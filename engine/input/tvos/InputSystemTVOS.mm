// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#include "InputSystemTVOS.hpp"
#include "GamepadDeviceTVOS.hpp"
#include "../../core/Engine.hpp"
#include "../../core/tvos/NativeWindowTVOS.hpp"
#include "../../utils/Log.hpp"

@interface ConnectDelegate: NSObject

@end

@implementation ConnectDelegate
{
    ouzel::input::InputSystemTVOS* input;
}

- (id)initWithInput:(ouzel::input::InputSystemTVOS*)initInput
{
    if (self = [super init])
        input = initInput;

    return self;
}

- (void)handleControllerConnected:(NSNotification*)notification
{
    input->handleGamepadConnected(notification.object);
}

- (void)handleControllerDisconnected:(NSNotification*)notification
{
    input->handleGamepadDisconnected(notification.object);
}
@end

namespace ouzel
{
    namespace input
    {
        InputSystemTVOS::InputSystemTVOS(const std::function<std::future<bool>(const Event&)>& initCallback):
            InputSystem(initCallback),
            keyboardDevice(std::make_unique<KeyboardDevice>(*this, getNextDeviceId()))
        {
            connectDelegate = [[ConnectDelegate alloc] initWithInput:this];

            [[NSNotificationCenter defaultCenter] addObserver:connectDelegate
                                                     selector:@selector(handleControllerConnected:)
                                                         name:GCControllerDidConnectNotification
                                                       object:nil];

            [[NSNotificationCenter defaultCenter] addObserver:connectDelegate
                                                     selector:@selector(handleControllerDisconnected:)
                                                         name:GCControllerDidDisconnectNotification
                                                       object:nil];

            for (GCController* controller in [GCController controllers])
                handleGamepadConnected(controller);

            [GCController startWirelessControllerDiscoveryWithCompletionHandler:
             ^(void){ handleGamepadDiscoveryCompleted(); }];
        }

        InputSystemTVOS::~InputSystemTVOS()
        {
            if (connectDelegate)
            {
                [[NSNotificationCenter defaultCenter] removeObserver:connectDelegate];

                [connectDelegate release];
            }
        }

        void InputSystemTVOS::executeCommand(const Command& command)
        {
            switch (command.type)
            {
                case Command::Type::StartDeviceDiscovery:
                    startGamepadDiscovery();
                    break;
                case Command::Type::StopDeviceDiscovery:
                    stopGamepadDiscovery();
                    break;
                case Command::Type::SetAbsoluteDpad_VALUES:
                {
                    if (InputDevice* inputDevice = getInputDevice(command.deviceId))
                    {
                        GamepadDeviceTVOS* gamepadDevice = static_cast<GamepadDeviceTVOS*>(inputDevice);
                        gamepadDevice->setAbsoluteDpadValues(command.absoluteDpadValues);
                    }
                    break;
                }
                case Command::Type::SetPlayerIndex:
                {
                    if (InputDevice* inputDevice = getInputDevice(command.deviceId))
                    {
                        GamepadDeviceTVOS* gamepadDevice = static_cast<GamepadDeviceTVOS*>(inputDevice);
                        gamepadDevice->setPlayerIndex(command.playerIndex);
                    }
                    break;
                }
                case Command::Type::SetVibration:
                {
                    break;
                }
                case Command::Type::ShowVirtualKeyboard:
                    showVirtualKeyboard();
                    break;
                case Command::Type::HideVirtualKeyboard:
                    hideVirtualKeyboard();
                    break;
                default:
                    break;
            }
        }

        void InputSystemTVOS::startGamepadDiscovery()
        {
            [GCController startWirelessControllerDiscoveryWithCompletionHandler:
             ^(void){ handleGamepadDiscoveryCompleted(); }];
        }

        void InputSystemTVOS::stopGamepadDiscovery()
        {
            [GCController stopWirelessControllerDiscovery];
        }

        void InputSystemTVOS::handleGamepadDiscoveryCompleted()
        {
            sendEvent(Event(Event::Type::DeviceDiscoveryComplete));
        }

        void InputSystemTVOS::handleGamepadConnected(GCControllerPtr controller)
        {
            std::vector<std::int32_t> playerIndices = {0, 1, 2, 3};

            for (const auto& i : gamepadDevices)
            {
                auto n = std::find(playerIndices.begin(), playerIndices.end(), i.second->getPlayerIndex());
                if (n != playerIndices.end()) playerIndices.erase(n);
            }

            if (!playerIndices.empty()) controller.playerIndex = static_cast<GCControllerPlayerIndex>(playerIndices.front());

            auto gamepadDevice = std::make_unique<GamepadDeviceTVOS>(*this, getNextDeviceId(), controller);
            gamepadDevices.insert(std::make_pair(controller, std::move(gamepadDevice)));
        }

        void InputSystemTVOS::handleGamepadDisconnected(GCControllerPtr controller)
        {
            auto i = gamepadDevices.find(controller);

            if (i != gamepadDevices.end())
                gamepadDevices.erase(i);
        }

        void InputSystemTVOS::showVirtualKeyboard()
        {
            NativeWindowTVOS* windowTVOS = static_cast<NativeWindowTVOS*>(engine->getWindow()->getNativeWindow());
            UITextField* textField = windowTVOS->getTextField();
            [textField becomeFirstResponder];
        }

        void InputSystemTVOS::hideVirtualKeyboard()
        {
            NativeWindowTVOS* windowTVOS = static_cast<NativeWindowTVOS*>(engine->getWindow()->getNativeWindow());
            UITextField* textField = windowTVOS->getTextField();
            [textField resignFirstResponder];
        }
    } // namespace input
} // namespace ouzel
