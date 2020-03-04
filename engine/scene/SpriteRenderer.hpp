// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_SCENE_SPRITE_HPP
#define OUZEL_SCENE_SPRITE_HPP

#include <list>
#include <map>
#include <memory>
#include <vector>
#include "scene/Component.hpp"
#include "math/Box.hpp"
#include "math/Rect.hpp"
#include "math/Size.hpp"
#include "math/Vector.hpp"
#include "events/EventHandler.hpp"
#include "graphics/BlendState.hpp"
#include "graphics/Buffer.hpp"
#include "graphics/Material.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Vertex.hpp"

namespace ouzel
{
    namespace scene
    {
        class SpriteData final
        {
        public:
            class Frame final
            {
            public:
                Frame(const std::string& frameName,
                      const Size2F& textureSize,
                      const RectF& frameRectangle,
                      bool rotated,
                      const Size2F& sourceSize,
                      const Vector2F& sourceOffset,
                      const Vector2F& pivot);

                Frame(const std::string& frameName,
                      const std::vector<uint16_t>& indices,
                      const std::vector<graphics::Vertex>& vertices);

                Frame(const std::string& frameName,
                      const std::vector<uint16_t>& indices,
                      const std::vector<graphics::Vertex>& vertices,
                      const RectF& frameRectangle,
                      const Size2F& sourceSize,
                      const Vector2F& sourceOffset,
                      const Vector2F& pivot);

                inline auto& getName() const noexcept { return name; }

                inline auto& getBoundingBox() const noexcept { return boundingBox; }
                inline auto getIndexCount() const noexcept { return indexCount; }
                inline auto& getIndexBuffer() const noexcept { return indexBuffer; }
                inline auto& getVertexBuffer() const noexcept { return vertexBuffer; }

            private:
                std::string name;
                Box2F boundingBox;
                uint32_t indexCount = 0;
                std::shared_ptr<graphics::Buffer> indexBuffer;
                std::shared_ptr<graphics::Buffer> vertexBuffer;
            };

            struct Animation final
            {
                std::string name;
                std::vector<Frame> frames;
                float frameInterval = 0.1F;
            };

            std::map<std::string, Animation> animations;
            std::shared_ptr<graphics::Texture> texture;
            const graphics::BlendState* blendState = nullptr;
            const graphics::Shader* shader = nullptr;
        };

        class SpriteRenderer: public Component
        {
        public:
            SpriteRenderer();
            explicit SpriteRenderer(const SpriteData& spriteData);
            explicit SpriteRenderer(const std::string& filename);
            explicit SpriteRenderer(std::shared_ptr<graphics::Texture> texture,
                                    uint32_t spritesX = 1, uint32_t spritesY = 1,
                                    const Vector2F& pivot = Vector2F{0.5F, 0.5F});

            void init(const SpriteData& spriteData);
            void init(const std::string& filename);
            void init(std::shared_ptr<graphics::Texture> newTexture,
                      uint32_t spritesX = 1, uint32_t spritesY = 1,
                      const Vector2F& pivot = Vector2F{0.5F, 0.5F});

            void update(float delta);

            void draw(const Matrix4F& transformMatrix,
                      float opacity,
                      const Matrix4F& renderViewProjection,
                      bool wireframe) override;

            inline auto& getMaterial() const noexcept { return material; }
            inline void setMaterial(const std::shared_ptr<graphics::Material>& newMaterial) { material = newMaterial; }

            inline auto& getOffset() const noexcept { return offset; }
            void setOffset(const Vector2F& newOffset);

            void play();
            void stop(bool resetAnimation = true);
            void reset();
            inline auto isPlaying() const noexcept { return playing; }

            inline auto& getAnimations() const noexcept { return animations; }
            inline auto getAnimation() const noexcept { return currentAnimation->animation; }
            inline auto& getAnimationName() const noexcept { return currentAnimation->animation->name; }
            bool hasAnimation(const std::string& animation) const;
            void setAnimation(const std::string& newAnimation, bool repeat = true);
            void addAnimation(const std::string& newAnimation, bool repeat = true);
            void setAnimationProgress(float progress);
            void setAnimationTime(float time);

        private:
            void updateBoundingBox();

            std::shared_ptr<graphics::Material> material;
            std::map<std::string, SpriteData::Animation> animations;

            struct QueuedAnimation final
            {
                const SpriteData::Animation* animation;
                bool repeat;
            };

            std::list<QueuedAnimation> animationQueue;
            std::list<QueuedAnimation>::const_iterator currentAnimation;

            Vector2F offset;
            Matrix4F offsetMatrix = Matrix4F::identity();

            bool playing = false;
            bool running = false;
            float currentTime = 0.0F;

            EventHandler updateHandler;
        };
    } // namespace scene
} // namespace ouzel

#endif // OUZEL_SCENE_SPRITE_HPP
