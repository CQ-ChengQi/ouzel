// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_SOUND_HPP
#define OUZEL_AUDIO_SOUND_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace ouzel
{
    namespace audio
    {
        class Audio;

        class Sound
        {
            friend Audio;
        public:
            enum class Format
            {
                Pcm,
                Vorbis
            };

            Sound(Audio& initAudio, uintptr_t initSourceId, Format initFormat);
            virtual ~Sound();

            Sound(const Sound&) = delete;
            Sound& operator=(const Sound&) = delete;

            Sound(Sound&&) = delete;
            Sound& operator=(Sound&&) = delete;

            inline auto getSourceId() const noexcept { return sourceId; }
            inline auto getFormat() const noexcept { return format; }

        protected:
            Audio& audio;
            uintptr_t sourceId = 0;
            Format format;
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_SOUND_HPP
