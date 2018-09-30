// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#include "input/InputSystem.hpp"
#include "input/windows/GamepadDeviceWin.hpp"

namespace ouzel
{
    namespace input
    {
        class InputSystemWin: public InputSystem
        {
        public:
            virtual ~InputSystemWin() {}

            static Keyboard::Key convertKeyCode(UINT keyCode);
            static uint32_t getModifiers(WPARAM wParam);

            void handleButtonValueChange(const GamepadDeviceWin& gamepad, Gamepad::Button button, bool pressed, float value);
        };
    }
}