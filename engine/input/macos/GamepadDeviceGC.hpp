// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_INPUT_GAMEPADDEVICEGC_HPP
#define OUZEL_INPUT_GAMEPADDEVICEGC_HPP

#if defined(__OBJC__)
#  include <GameController/GameController.h>
typedef GCController* GCControllerPtr;
#else
#  include <objc/objc.h>
typedef id GCControllerPtr;
#endif

#include "GamepadDeviceMacOS.hpp"
#include "../Gamepad.hpp"

namespace ouzel
{
    namespace input
    {
        class GamepadDeviceGC final: public GamepadDeviceMacOS
        {
        public:
            GamepadDeviceGC(InputSystem& initInputSystem,
                            DeviceId initId,
                            GCControllerPtr initController);

            void setAbsoluteDpadValues(bool absoluteDpadValues);
            bool isAbsoluteDpadValues() const;

            std::int32_t getPlayerIndex() const;
            void setPlayerIndex(std::int32_t playerIndex) final;

            inline auto getController() const noexcept { return controller; }

        private:
            GCControllerPtr controller = nil;
            bool attached = false;
        };
    } // namespace input
} // namespace ouzel

#endif // OUZEL_INPUT_GAMEPADDEVICEGC_HPP
