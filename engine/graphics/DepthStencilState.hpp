// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_DEPTHSTENCILSTATE_HPP
#define OUZEL_GRAPHICS_DEPTHSTENCILSTATE_HPP

#include "graphics/RenderDevice.hpp"
#include "graphics/CompareFunction.hpp"
#include "graphics/StencilOperation.hpp"

namespace ouzel
{
    namespace graphics
    {
        class Renderer;

        class DepthStencilState final
        {
        public:
            DepthStencilState() = default;

            explicit DepthStencilState(Renderer& initRenderer);
            DepthStencilState(Renderer& initRenderer,
                              bool initDepthTest,
                              bool initDepthWrite,
                              CompareFunction initCompareFunction,
                              bool initStencilEnabled,
                              uint32_t initStencilReadMask,
                              uint32_t initStencilWriteMask,
                              StencilOperation initFrontFaceStencilFailureOperation,
                              StencilOperation initFrontFaceStencilDepthFailureOperation,
                              StencilOperation initFrontFaceStencilPassOperation,
                              CompareFunction initFrontFaceStencilCompareFunction,
                              StencilOperation initBackFaceStencilFailureOperation,
                              StencilOperation initBackFaceStencilDepthFailureOperation,
                              StencilOperation initBackFaceStencilPassOperation,
                              CompareFunction initBackFaceStencilCompareFunction);

            inline auto& getResource() const noexcept { return resource; }

        private:
            RenderDevice::Resource resource;

            bool depthTest = false;
            bool depthWrite = false;
            CompareFunction compareFunction;
            bool stencilEnabled = false;
            uint32_t stencilReadMask = 0xFFFFFFFF;
            uint32_t stencilWriteMask = 0xFFFFFFFF;
            StencilOperation frontFaceStencilFailureOperation;
            StencilOperation frontFaceStencilDepthFailureOperation;
            StencilOperation frontFaceStencilPassOperation;
            CompareFunction frontFaceStencilCompareFunction;
            StencilOperation backFaceStencilFailureOperation;
            StencilOperation backFaceStencilDepthFailureOperation;
            StencilOperation backFaceStencilPassOperation;
            CompareFunction backFaceStencilCompareFunction;
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_DEPTHSTENCILSTATE_HPP
