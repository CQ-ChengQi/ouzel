// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#include <system_error>
#include "GamepadDeviceXI.hpp"

namespace ouzel
{
    namespace input
    {
        namespace
        {
            constexpr std::int32_t MAX_THUMB_VALUE = 32767;
            constexpr std::int32_t MIN_THUMB_VALUE = -32768;
        }

        GamepadDeviceXI::GamepadDeviceXI(InputSystem& initInputSystem,
                                         DeviceId initId,
                                         DWORD aPlayerIndex):
            GamepadDeviceWin(initInputSystem, initId),
            playerIndex(aPlayerIndex)
        {
        }

        void GamepadDeviceXI::update()
        {
            XINPUT_STATE newState = {};
            DWORD result = XInputGetState(playerIndex, &newState);

            if (result != ERROR_SUCCESS)
            {
                if (result == ERROR_DEVICE_NOT_CONNECTED)
                    throw std::runtime_error("Gamepad " + std::to_string(playerIndex) + " disconnected");
                else
                    throw std::system_error(result, std::system_category(), "Failed to get state for gamepad " + std::to_string(playerIndex));
            }

            if (newState.dwPacketNumber > state.dwPacketNumber)
            {
                // buttons
                checkButton(newState, XINPUT_GAMEPAD_DPAD_UP, Gamepad::Button::DpadUp);
                checkButton(newState, XINPUT_GAMEPAD_DPAD_DOWN, Gamepad::Button::DpadDown);
                checkButton(newState, XINPUT_GAMEPAD_DPAD_LEFT, Gamepad::Button::DpadLeft);
                checkButton(newState, XINPUT_GAMEPAD_DPAD_RIGHT, Gamepad::Button::DpadRight);
                checkButton(newState, XINPUT_GAMEPAD_START, Gamepad::Button::Start);
                checkButton(newState, XINPUT_GAMEPAD_BACK, Gamepad::Button::Back);
                checkButton(newState, XINPUT_GAMEPAD_LEFT_THUMB, Gamepad::Button::LeftThumb);
                checkButton(newState, XINPUT_GAMEPAD_RIGHT_THUMB, Gamepad::Button::RightThumb);
                checkButton(newState, XINPUT_GAMEPAD_LEFT_SHOULDER, Gamepad::Button::LeftShoulder);
                checkButton(newState, XINPUT_GAMEPAD_RIGHT_SHOULDER, Gamepad::Button::RightShoulder);
                checkButton(newState, XINPUT_GAMEPAD_A, Gamepad::Button::FaceBottom);
                checkButton(newState, XINPUT_GAMEPAD_B, Gamepad::Button::FaceRight);
                checkButton(newState, XINPUT_GAMEPAD_X, Gamepad::Button::FaceLeft);
                checkButton(newState, XINPUT_GAMEPAD_Y, Gamepad::Button::FaceTop);

                // triggers
                if (newState.Gamepad.bLeftTrigger != state.Gamepad.bLeftTrigger)
                {
                    handleButtonValueChange(Gamepad::Button::LeftTrigger,
                                            newState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD,
                                            static_cast<float>(newState.Gamepad.bLeftTrigger) / 255.0F);
                }

                if (newState.Gamepad.bRightTrigger != state.Gamepad.bRightTrigger)
                {
                    handleButtonValueChange(Gamepad::Button::RightTrigger,
                                            newState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD,
                                            static_cast<float>(newState.Gamepad.bRightTrigger) / 255.0F);
                }

                // left thumbstick
                checkThumbAxis(state.Gamepad.sThumbLX, newState.Gamepad.sThumbLX, Gamepad::Button::LeftThumbLeft, Gamepad::Button::LeftThumbRight);
                checkThumbAxis(state.Gamepad.sThumbLY, newState.Gamepad.sThumbLY, Gamepad::Button::LeftThumbDown, Gamepad::Button::LeftThumbUp);

                // right thumbstick
                checkThumbAxis(state.Gamepad.sThumbRX, newState.Gamepad.sThumbRX, Gamepad::Button::RightThumbLeft, Gamepad::Button::RightThumbRight);
                checkThumbAxis(state.Gamepad.sThumbRY, newState.Gamepad.sThumbRY, Gamepad::Button::RightThumbDown, Gamepad::Button::RightThumbUp);

                state = newState;
            }
        }

        std::int32_t GamepadDeviceXI::getPlayerIndex() const
        {
            return static_cast<std::int32_t>(playerIndex);
        }

        void GamepadDeviceXI::checkThumbAxis(SHORT oldValue, SHORT newValue, Gamepad::Button negativeButton, Gamepad::Button positiveButton)
        {
            if (newValue != oldValue)
            {
                if (newValue > 0)
                {
                    handleButtonValueChange(positiveButton,
                                            newValue > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,
                                            static_cast<float>(newValue) / static_cast<float>(MAX_THUMB_VALUE));
                }
                else if (newValue < 0)
                {
                    handleButtonValueChange(negativeButton,
                                            newValue < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,
                                            static_cast<float>(newValue) / static_cast<float>(MIN_THUMB_VALUE));
                }
                else // thumbstick is 0
                {
                    if (oldValue > newValue)
                        handleButtonValueChange(positiveButton, false, 0.0F);
                    else
                        handleButtonValueChange(negativeButton, false, 0.0F);
                }
            }
        }

        void GamepadDeviceXI::checkButton(const XINPUT_STATE& newState, WORD mask, Gamepad::Button button)
        {
            if ((newState.Gamepad.wButtons & mask) != (state.Gamepad.wButtons & mask))
            {
                const bool pressed = ((newState.Gamepad.wButtons & mask) == mask);
                handleButtonValueChange(button, pressed, pressed ? 1.0F : 0.0F);
            }
        }

        void GamepadDeviceXI::setVibration(Gamepad::Motor motor, float speed)
        {
            switch (motor)
            {
            case Gamepad::Motor::All:
                vibration.wLeftMotorSpeed = static_cast<WORD>(speed);
                vibration.wRightMotorSpeed = static_cast<WORD>(speed);
                break;
            case Gamepad::Motor::Left:
                vibration.wLeftMotorSpeed = static_cast<WORD>(speed);
                break;
            case Gamepad::Motor::Right:
                vibration.wRightMotorSpeed = static_cast<WORD>(speed);
                break;
            default:
                return;
            }

            XInputSetState(playerIndex, &vibration);
        }

        float GamepadDeviceXI::getVibration(Gamepad::Motor motor)
        {
            switch (motor)
            {
            case Gamepad::Motor::All:
            case Gamepad::Motor::Left:
                return vibration.wLeftMotorSpeed;
            case Gamepad::Motor::Right:
                return vibration.wRightMotorSpeed;
            default:
                return 0.0f;
            }
        }
    } // namespace input
} // namespace ouzel
