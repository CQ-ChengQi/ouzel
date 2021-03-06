// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_METALRENDERDEVICE_HPP
#define OUZEL_GRAPHICS_METALRENDERDEVICE_HPP

#include "../../core/Setup.h"

#if OUZEL_COMPILE_METAL

#include <map>
#include <memory>
#include <vector>
#include <dispatch/dispatch.h>

#if defined(__OBJC__)
#  import <CoreVideo/CoreVideo.h>
#  import <QuartzCore/QuartzCore.h>
#  import <Metal/Metal.h>
typedef CAMetalLayer* CAMetalLayerPtr;
typedef id<MTLDevice> MTLDevicePtr;
typedef id<MTLBuffer> MTLBufferPtr;
typedef MTLRenderPassDescriptor* MTLRenderPassDescriptorPtr;
typedef id<MTLSamplerState> MTLSamplerStatePtr;
typedef id<MTLCommandQueue> MTLCommandQueuePtr;
typedef id<MTLRenderPipelineState> MTLRenderPipelineStatePtr;
typedef id<MTLTexture> MTLTexturePtr;
typedef id<MTLDepthStencilState> MTLDepthStencilStatePtr;
#else
#  include <objc/objc.h>
#  include <objc/NSObjCRuntime.h>
typedef id CAMetalLayerPtr;
typedef id MTLDevicePtr;
typedef id MTLBufferPtr;
typedef id MTLRenderPassDescriptorPtr;
typedef id MTLSamplerStatePtr;
typedef id MTLCommandBufferPtr;
typedef id MTLCommandQueuePtr;
typedef id MTLRenderCommandEncoderPtr;
typedef id MTLRenderPipelineStatePtr;
typedef id MTLTexturePtr;
typedef id MTLDepthStencilStatePtr;
typedef NSUInteger MTLPixelFormat;
typedef NSUInteger MTLLoadAction;
#endif

#include "../RenderDevice.hpp"
#include "MetalPointer.hpp"
#include "MetalShader.hpp"
#include "MetalTexture.hpp"

namespace ouzel
{
    namespace graphics
    {
        namespace metal
        {
            class BlendState;
            class Shader;

            class RenderDevice: public graphics::RenderDevice
            {
                friend Renderer;
            public:
                static constexpr std::size_t BUFFER_SIZE = 1024 * 1024; // size of shader constant buffer
                static constexpr std::size_t BUFFER_COUNT = 3; // allow encoding up to 3 command buffers simultaneously

                static bool available();

                inline auto& getDevice() const noexcept { return device; }

                MTLSamplerStatePtr getSamplerState(const SamplerStateDescriptor& descriptor);

                template <class T>
                inline auto getResource(std::uintptr_t id) const
                {
                    return id ? static_cast<T*>(resources[id - 1].get()) : nullptr;
                }

            protected:
                explicit RenderDevice(const std::function<void(const Event&)>& initCallback);

                void init(Window* newWindow,
                          const Size2U& newSize,
                          std::uint32_t newSampleCount,
                          SamplerFilter newTextureFilter,
                          std::uint32_t newMaxAnisotropy,
                          bool newSrgb,
                          bool newVerticalSync,
                          bool newDepth,
                          bool newStencil,
                          bool newDebugRenderer) override;

                void process() override;
                void generateScreenshot(const std::string& filename) override;

                class PipelineStateDesc final
                {
                public:
                    BlendState* blendState = nullptr;
                    Shader* shader = nullptr;
                    NSUInteger sampleCount = 0;
                    std::vector<MTLPixelFormat> colorFormats;
                    MTLPixelFormat depthFormat;
                    MTLPixelFormat stencilFormat;

                    bool operator<(const PipelineStateDesc& other) const noexcept
                    {
                        return std::tie(blendState, shader, sampleCount, colorFormats, depthFormat) <
                            std::tie(other.blendState, other.shader, other.sampleCount, colorFormats, other.depthFormat);
                    }
                };

                MTLRenderPipelineStatePtr getPipelineState(const PipelineStateDesc& desc);

                Pointer<MTLDevicePtr> device;
                Pointer<MTLCommandQueuePtr> metalCommandQueue;
                CAMetalLayerPtr metalLayer = nil;
                Pointer<MTLTexturePtr> currentMetalTexture;

                struct ShaderConstantBuffer
                {
                    std::vector<Pointer<MTLBufferPtr>> buffers;
                    std::uint32_t index = 0;
                    std::uint32_t offset = 0;
                };

                std::uint32_t shaderConstantBufferIndex = 0;
                ShaderConstantBuffer shaderConstantBuffers[BUFFER_COUNT];

                Pointer<MTLRenderPassDescriptorPtr> renderPassDescriptor;
                Pointer<MTLDepthStencilStatePtr> defaultDepthStencilState;

                Pointer<MTLTexturePtr> msaaTexture;
                Pointer<MTLTexturePtr> depthTexture;
                std::map<SamplerStateDescriptor, Pointer<MTLSamplerStatePtr>> samplerStates;

                MTLPixelFormat colorFormat;
                MTLPixelFormat depthFormat;
                MTLPixelFormat stencilFormat;

                dispatch_semaphore_t inflightSemaphore;

                std::map<PipelineStateDesc, Pointer<MTLRenderPipelineStatePtr>> pipelineStates;

                std::vector<std::unique_ptr<RenderResource>> resources;
            };
        } // namespace metal
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_METALRENDERDEVICE_HPP
