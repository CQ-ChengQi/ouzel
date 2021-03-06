// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_D3D11RENDERRESOURCE_HPP
#define OUZEL_GRAPHICS_D3D11RENDERRESOURCE_HPP

#include "../../core/Setup.h"

#if OUZEL_COMPILE_DIRECT3D11

namespace ouzel
{
    namespace graphics
    {
        namespace d3d11
        {
            class RenderDevice;

            class RenderResource
            {
            public:
                explicit RenderResource(RenderDevice& initRenderDevice):
                    renderDevice(initRenderDevice)
                {
                }

                virtual ~RenderResource() = default;

                RenderResource(const RenderResource&) = delete;
                RenderResource& operator=(const RenderResource&) = delete;

                RenderResource(RenderResource&&) = delete;
                RenderResource& operator=(RenderResource&&) = delete;

            protected:
                RenderDevice& renderDevice;
            };
        } // namespace d3d11
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_D3D11RENDERRESOURCE_HPP
