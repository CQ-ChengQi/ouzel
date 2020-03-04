// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_STENCILPERATION_HPP
#define OUZEL_GRAPHICS_STENCILPERATION_HPP

namespace ouzel
{
    namespace graphics
    {
        enum class StencilOperation
        {
            Keep,
            Zero,
            Replace,
            IncrementClamp,
            DecrementClamp,
            Invert,
            IncrementWrap,
            DecrementWrap
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_STENCILPERATION_HPP
