// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_OGLTEXTURE_HPP
#define OUZEL_GRAPHICS_OGLTEXTURE_HPP

#include <array>
#include <utility>

#include "core/Setup.h"

#if OUZEL_COMPILE_OPENGL

#include "graphics/opengl/OGL.h"

#if OUZEL_OPENGLES
#  include "GLES/gl.h"
#  include "GLES2/gl2.h"
#  include "GLES2/gl2ext.h"
#  include "GLES3/gl3.h"
#else
#  include "GL/glcorearb.h"
#  include "GL/glext.h"
#endif

#include "graphics/opengl/OGLRenderResource.hpp"
#include "graphics/PixelFormat.hpp"
#include "graphics/SamplerAddressMode.hpp"
#include "graphics/SamplerFilter.hpp"
#include "graphics/TextureType.hpp"
#include "math/Size.hpp"

namespace ouzel
{
    namespace graphics
    {
        namespace opengl
        {
            class RenderDevice;

            class Texture final: public RenderResource
            {
            public:
                Texture(RenderDevice& initRenderDevice,
                        const std::vector<std::pair<Size2U, std::vector<uint8_t>>>& initLevels,
                        TextureType type,
                        uint32_t initFlags = 0,
                        uint32_t initSampleCount = 1,
                        PixelFormat initPixelFormat = PixelFormat::RGBA8UNorm);
                ~Texture();

                void reload() final;

                void setData(const std::vector<std::pair<Size2U, std::vector<uint8_t>>>& newLevels);
                void setFilter(SamplerFilter newFilter);
                void setAddressX(SamplerAddressMode newAddressX);
                void setAddressY(SamplerAddressMode newAddressY);
                void setAddressZ(SamplerAddressMode newAddressZ);
                void setMaxAnisotropy(uint32_t newMaxAnisotropy);

                inline auto getFlags() const noexcept { return flags; }
                inline auto getMipmaps() const noexcept { return mipmaps; }

                inline auto getFilter() const noexcept { return filter; }
                inline auto getAddressX() const noexcept { return addressX; }
                inline auto getAddressY() const noexcept { return addressY; }
                inline auto getMaxAnisotropy() const noexcept { return maxAnisotropy; }
                inline auto getSampleCount() const noexcept { return sampleCount; }

                inline auto getTextureId() const noexcept { return textureId; }
                inline auto getBufferId() const noexcept { return bufferId; }

                inline auto getWidth() const noexcept { return width; }
                inline auto getHeight() const noexcept { return height; }

                inline auto getPixelFormat() const noexcept { return pixelFormat; }

            private:
                void createTexture();
                void setTextureParameters();

                std::vector<std::pair<Size2U, std::vector<uint8_t>>> levels;
                uint32_t flags = 0;
                uint32_t mipmaps = 0;
                uint32_t sampleCount = 1;
                SamplerFilter filter = SamplerFilter::Default;
                SamplerAddressMode addressX = SamplerAddressMode::ClampToEdge;
                SamplerAddressMode addressY = SamplerAddressMode::ClampToEdge;
                SamplerAddressMode addressZ = SamplerAddressMode::ClampToEdge;
                uint32_t maxAnisotropy = 0;

                GLenum textureTarget = 0;
                GLuint textureId = 0;
                GLuint bufferId = 0;

                GLsizei width = 0;
                GLsizei height = 0;
                GLenum internalPixelFormat = GL_NONE;
                GLenum pixelFormat = GL_NONE;
                GLenum pixelType = GL_NONE;
            };
        } // namespace opengl
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_OGLTEXTURE_HPP
