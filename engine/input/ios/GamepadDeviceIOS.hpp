// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_INPUT_GAMEPADDEVICEIOS_HPP
#define OUZEL_INPUT_GAMEPADDEVICEIOS_HPP

#include <string>
#if defined(__OBJC__)
#  include <GameController/GameController.h>
typedef GCController* GCControllerPtr;
#else
#  include <objc/objc.h>
typedef id GCControllerPtr;
#endif

#include "../GamepadDevice.hpp"
#include "../Gamepad.hpp"

namespace ouzel
{
    namespace input
    {
        class GamepadDeviceIOS final: public GamepadDevice
        {
        public:
            GamepadDeviceIOS(InputSystem& initInputSystem,
                             DeviceId initId,
                             GCControllerPtr initController);

            void setAbsoluteDpadValues(bool absoluteDpadValues);
            bool isAbsoluteDpadValues() const;

            std::int32_t getPlayerIndex() const;
            void setPlayerIndex(std::int32_t playerIndex);

            inline auto getController() const noexcept { return controller; }

        private:
            GCControllerPtr controller = nil;
            std::string name;
            bool attached = false;
        };
    } // namespace input
} // namespace ouzel

#endif // OUZEL_INPUT_GAMEPADDEVICEIOS_HPP
