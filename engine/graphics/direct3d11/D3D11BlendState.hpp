// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_D3D11BLENDSTATE_HPP
#define OUZEL_GRAPHICS_D3D11BLENDSTATE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_DIRECT3D11

#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("NOMINMAX")
#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#  define NOMINMAX
#endif
#include <d3d11.h>
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOMINMAX")

#include "graphics/direct3d11/D3D11RenderResource.hpp"
#include "graphics/direct3d11/D3D11Pointer.hpp"
#include "graphics/BlendFactor.hpp"
#include "graphics/BlendOperation.hpp"
#include "graphics/ColorMask.hpp"

namespace ouzel
{
    namespace graphics
    {
        namespace d3d11
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

                inline auto& getBlendState() const noexcept { return blendState; }

            private:
                Pointer<ID3D11BlendState> blendState;
            };
        } // namespace d3d11
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_D3D11BLENDSTATE_HPP