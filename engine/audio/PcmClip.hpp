// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_PCMCLIP_HPP
#define OUZEL_AUDIO_PCMCLIP_HPP

#include <cstdint>
#include <vector>
#include "audio/Sound.hpp"

namespace ouzel
{
    namespace audio
    {
        class PcmData;

        class PcmClip final: public Sound
        {
        public:
            PcmClip(Audio& initAudio, uint32_t channels, uint32_t sampleRate,
                    const std::vector<float>& samples);

        private:
            PcmData* data;
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_PCMCLIP_HPP
