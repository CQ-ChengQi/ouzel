// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_SCENE_LIGHT_HPP
#define OUZEL_SCENE_LIGHT_HPP

#include "scene/Component.hpp"
#include "math/Color.hpp"
#include "math/Quaternion.hpp"

namespace ouzel
{
    namespace scene
    {
        class Light: public Component
        {
        public:
            enum class Type
            {
                Point,
                Spot,
                Directional
            };

            Light() = default;
            explicit Light(Type initType);
            ~Light() override;

            inline auto getType() const noexcept { return type; }
            inline void setType(Type newType) { type = newType; }

            inline auto getColor() const noexcept { return color; }
            inline void setColor(Color newColor) { color = newColor; }

            inline auto& getDirection() const noexcept { return direction; }
            inline void setDirection(const QuaternionF& newDirection) { direction = newDirection; }

            inline auto getAngle() const noexcept { return angle; }
            inline void setAngle(float newAngle) { angle = newAngle; }

            inline auto getRange() const noexcept { return range; }
            inline void setRange(float newRange) { range = newRange; }

            inline auto getIntensity() const noexcept { return intensity; }
            inline void setIntensity(float newIntensity) { intensity = newIntensity; }

        private:
            void setLayer(Layer* newLayer) override;

            Type type = Type::Point;
            Color color;
            QuaternionF direction = QuaternionF::identity(); // for spot and directional ligt
            float angle = 0.0F; // for spot light
            float range = 0.0F; // for point and spot light
            float intensity = 1.0F;
        };
    } // namespace scene
} // namespace ouzel

#endif // OUZEL_SCENE_LIGHT_HPP
