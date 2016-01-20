// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "TextureOGL.h"
#include "Engine.h"
#include "RendererOGL.h"
#include "Image.h"
#include "Utils.h"
#include "stb_image_resize.h"

namespace ouzel
{
    TextureOGL::TextureOGL()
    {
        
    }
    
    TextureOGL::~TextureOGL()
    {
        clean();
    }
    
    void TextureOGL::clean()
    {
        if (_textureId) glDeleteTextures(1, &_textureId);
    }
    
    bool TextureOGL::init(const Size2& size, bool dynamic)
    {
        if (!Texture::init(size, dynamic))
        {
            return false;
        }
        
        clean();
        
        glGenTextures(1, &_textureId);
        
        if (size.width > 0.0f && size.height > 0.0f)
        {
            glBindTexture(GL_TEXTURE_2D, _textureId);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                         static_cast<GLsizei>(size.width),
                         static_cast<GLsizei>(size.height),
                         0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        return true;
    }
    
    bool TextureOGL::initFromData(const void* data, const Size2& size, bool dynamic)
    {
        if (!Texture::initFromData(data, size, dynamic))
        {
            return false;
        }
        
        clean();
        
        glGenTextures(1, &_textureId);
        
        glBindTexture(GL_TEXTURE_2D, _textureId);
        
        return uploadData(data,
                          static_cast<GLsizei>(size.width),
                          static_cast<GLsizei>(size.height));
    }
    
    bool TextureOGL::upload(const void* data, const Size2& size)
    {
        if (!Texture::upload(data, size))
        {
            return false;
        }
        
        return uploadData(data,
                          static_cast<GLsizei>(size.width),
                          static_cast<GLsizei>(size.height));
    }
    
    bool TextureOGL::uploadData(const void* data, GLsizei width, GLsizei height)
    {
        if (width <= 0 || height <= 0)
        {
            return false;
        }
        
        glBindTexture(GL_TEXTURE_2D, _textureId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        GLsizei mipWidth = width / 2;
        GLsizei mipHeight = height / 2;
        GLint mipLevel = 1;
        
        std::unique_ptr<uint8_t[]> mipMapData(new uint8_t[width * height * 4]);
        
        while (mipWidth && mipHeight)
        {
            stbir_resize_uint8(static_cast<const uint8_t*>(data), width, height, 0, mipMapData.get(), mipWidth, mipHeight, 0, 4);
            
            glTexImage2D(GL_TEXTURE_2D, mipLevel, GL_RGBA, mipWidth, mipHeight,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, mipMapData.get());
            
            if (std::static_pointer_cast<RendererOGL>(Engine::getInstance()->getRenderer())->checkOpenGLErrors())
            {
                return false;
            }
            
            mipWidth /= 2;
            mipHeight /= 2;
            mipLevel++;
        }
        
        if (std::static_pointer_cast<RendererOGL>(Engine::getInstance()->getRenderer())->checkOpenGLErrors())
        {
            return false;
        }
        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        if (std::static_pointer_cast<RendererOGL>(Engine::getInstance()->getRenderer())->checkOpenGLErrors())
        {
            return false;
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        return true;
    }
}
