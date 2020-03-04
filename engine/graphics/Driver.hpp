// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_DRIVER_HPP
#define OUZEL_GRAPHICS_DRIVER_HPP

namespace ouzel
{
    namespace graphics
    {
        enum class Driver
        {
            Empty,
            OpenGL,
            Direct3D11,
            Metal
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_DRIVER_HPP
