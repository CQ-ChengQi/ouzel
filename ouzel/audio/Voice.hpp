// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_VOICE_HPP
#define OUZEL_AUDIO_VOICE_HPP

#include <memory>
#include "audio/Node.hpp"
#include "math/Vector.hpp"

namespace ouzel
{
    namespace audio
    {
        class Audio;
        class Mix;
        class Sound;

        class Voice final: public Node
        {
            friend Mix;
        public:
            explicit Voice(Audio& initAudio);
            Voice(Audio& initAudio, const std::shared_ptr<Sound>& initSound);
            ~Voice();

            Voice(const Voice&) = delete;
            Voice& operator=(const Voice&) = delete;
            Voice(Voice&& other):
                Node(other.audio),
                audio(other.audio)
            {

            }

            Voice& operator=(Voice&& other)
            {
                if (this == &other) return *this;

                return *this;
            }

            inline const std::shared_ptr<Sound>& getSound() const noexcept { return sound; }

            inline const Vector3F& getPosition() const noexcept { return position; }
            inline void setPosition(const Vector3F& newPosition) { position = newPosition; }

            inline const Vector3F& getVelocity() const noexcept { return velocity; }
            inline void setVelocity(const Vector3F& newVelocity) { velocity = newVelocity; }

            void play();
            void pause();
            void stop();

            inline auto isPlaying() const noexcept { return playing; }

            void setOutput(Mix* newOutput);

        private:
            Audio& audio;
            uintptr_t streamId;

            std::shared_ptr<Sound> sound;
            Vector3F position;
            Vector3F velocity;
            bool playing = false;

            Mix* output = nullptr;
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_VOICE_HPP
