// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_METALBLENDSTATE_HPP
#define OUZEL_GRAPHICS_METALBLENDSTATE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_METAL

#if defined(__OBJC__)
#  import <Metal/Metal.h>
#else
#  include <objc/objc.h>
typedef NSUInteger MTLBlendFactor;
typedef NSUInteger MTLBlendOperation;
typedef NSUInteger MTLColorWriteMask;
#endif

#include "graphics/metal/MetalRenderResource.hpp"
#include "graphics/BlendFactor.hpp"
#include "graphics/BlendOperation.hpp"
#include "graphics/ColorMask.hpp"

namespace ouzel
{
    namespace graphics
    {
        namespace metal
        {
            class RenderDevice;

            class BlendState final: public RenderResource
            {
            public:
                BlendState(RenderDevice& initRenderDevice,
                           bool enableBlending,
                           BlendFactor colorBlendSource,
                           BlendFactor colorBlendDest,
                           BlendOperation colorOperation,
                           BlendFactor alphaBlendSource,
                           BlendFactor alphaBlendDest,
                           BlendOperation alphaOperation,
                           ColorMask colorMask);

                inline auto getRgbBlendOperation() const noexcept { return rgbBlendOperation; }
                inline auto getAlphaBlendOperation() const noexcept { return alphaBlendOperation; }
                inline auto getSourceRgbBlendFactor() const noexcept { return sourceRgbBlendFactor; }
                inline auto getDestinationRgbBlendFactor() const noexcept { return destinationRgbBlendFactor; }
                inline auto getSourceAlphaBlendFactor() const noexcept { return sourceAlphaBlendFactor; }
                inline auto getDestinationAlphaBlendFactor() const noexcept { return destinationAlphaBlendFactor; }
                inline auto getColorWriteMask() const noexcept { return colorWriteMask; }
                inline auto isBlendingEnabled() const noexcept { return blendingEnabled; }

            private:
                MTLBlendOperation rgbBlendOperation;
                MTLBlendOperation alphaBlendOperation;
                MTLBlendFactor sourceRgbBlendFactor;
                MTLBlendFactor destinationRgbBlendFactor;
                MTLBlendFactor sourceAlphaBlendFactor;
                MTLBlendFactor destinationAlphaBlendFactor;
                MTLColorWriteMask colorWriteMask;
                bool blendingEnabled;
            };
        } // namespace metal
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_METALBLENDSTATE_HPP
