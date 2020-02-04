// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_INPUT_INPUTSYSTEM_HPP
#define OUZEL_INPUT_INPUTSYSTEM_HPP

#include <cstdint>
#include <future>
#include <set>
#include <unordered_map>
#include <vector>
#include "input/GamepadDevice.hpp"
#include "input/KeyboardDevice.hpp"
#include "input/MouseDevice.hpp"
#include "input/SystemCursor.hpp"
#include "input/TouchpadDevice.hpp"
#include "graphics/PixelFormat.hpp"
#include "math/Size.hpp"
#include "math/Vector.hpp"

namespace ouzel
{
    namespace input
    {
        class InputSystem
        {
            friend InputDevice;
            friend GamepadDevice;
            friend KeyboardDevice;
            friend MouseDevice;
            friend TouchpadDevice;
        public:
            class Command final
            {
            public:
                enum class Type
                {
                    StartDeviceDiscovery,
                    StopDeviceDiscovery,
                    SetAbsoluteDpad_VALUES,
                    SetPlayerIndex,
                    SetVibration,
                    SetPosition,
                    InitCursor,
                    DestroyCursor,
                    SetCursor,
                    SetCursorVisible,
                    SetCursorLocked,
                    ShowVirtualKeyboard,
                    HideVirtualKeyboard
                };

                Command() = default;
                explicit Command(Type initType): type(initType) {}

                Type type;
                DeviceId deviceId;

                union
                {
                    bool absoluteDpadValues;
                    int32_t playerIndex;
                    float speed;
                    bool visible;
                    bool locked;
                };

                Gamepad::Motor motor;
                Vector2F position;
                uintptr_t cursorResource;
                SystemCursor systemCursor;
                std::vector<uint8_t> data;
                Size2F size;
                graphics::PixelFormat pixelFormat;
                Vector2F hotSpot;
            };

            class Event final
            {
            public:
                enum class Type
                {
                    DeviceConnect,
                    DeviceDisconnect,
                    DeviceDiscoveryComplete,

                    GamepadButtonChange,

                    KeyboardKeyPress,
                    KeyboardKeyRelease,

                    MousePress,
                    MouseRelease,
                    MouseScroll,
                    MouseMove,
                    MouseRelativeMove,
                    MouseLockChanged,

                    TouchBegin,
                    TouchMove,
                    TouchEnd,
                    TouchCancel
                };

                Event() = default;
                explicit Event(Type initType): type(initType) {}

                Type type;
                Controller::Type deviceType;
                DeviceId deviceId;
                union
                {
                    Keyboard::Key keyboardKey;
                    Mouse::Button mouseButton;
                    Gamepad::Button gamepadButton;
                    uint64_t touchId;
                };
                bool screen = false;
                bool locked = false;
                bool pressed = false;
                bool previousPressed = false;
                float value = 0.0F; // force for touch events
                float previousValue = 0.0F;
                Vector2F difference;
                Vector2F position;
                Vector2F scroll;
                float force = 1.0F;
            };

            explicit InputSystem(const std::function<std::future<bool>(const Event&)>& initCallback);
            virtual ~InputSystem() = default;

            void addCommand(const Command& command);
            virtual void executeCommand(const Command&) {}

            auto getResourceId()
            {
                auto i = deletedResourceIds.begin();

                if (i == deletedResourceIds.end())
                    return ++lastResourceId; // zero is reserved for null resource
                else
                {
                    uintptr_t resourceId = *i;
                    deletedResourceIds.erase(i);
                    return resourceId;
                }
            }

            void deleteResourceId(uintptr_t resourceId)
            {
                deletedResourceIds.insert(resourceId);
            }

        protected:
            std::future<bool> sendEvent(const Event& event);
            void addInputDevice(InputDevice& inputDevice);
            void removeInputDevice(const InputDevice& inputDevice);
            InputDevice* getInputDevice(DeviceId id);

        private:
            std::function<std::future<bool>(const Event&)> callback;
            std::unordered_map<DeviceId, InputDevice*> inputDevices;

            uintptr_t lastResourceId = 0;
            std::set<uintptr_t> deletedResourceIds;
        };
    } // namespace input
} // namespace ouzel

#endif // OUZEL_INPUT_INPUTSYSTEM_HPP
