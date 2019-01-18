// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_MATERIAL_HPP
#define OUZEL_GRAPHICS_MATERIAL_HPP

#include <memory>
#include "graphics/Renderer.hpp"
#include "graphics/BlendState.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "math/Color.hpp"

namespace ouzel
{
    namespace graphics
    {
        class Material final
        {
        public:
            Material() = default;

            BlendState* blendState = nullptr;
            Shader* shader = nullptr;
            Texture* textures[Texture::LAYERS]{nullptr};
            graphics::CullMode cullMode = graphics::CullMode::BACK;
            Color diffuseColor = Color::WHITE;
            float opacity = 1.0F;
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_MATERIAL_HPP
