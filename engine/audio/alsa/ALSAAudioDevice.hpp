// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_ALSAAUDIODEVICE_HPP
#define OUZEL_AUDIO_ALSAAUDIODEVICE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_ALSA

#include <atomic>
#include <thread>
#include <alsa/asoundlib.h>

#include "audio/AudioDevice.hpp"
#include "utils/Thread.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace alsa
        {
            class AudioDevice final: public audio::AudioDevice
            {
            public:
                AudioDevice(uint32_t initBufferSize,
                            uint32_t initSampleRate,
                            uint32_t initChannels,
                            const std::function<void(uint32_t frames,
                                                     uint32_t channels,
                                                     uint32_t sampleRate,
                                                     std::vector<float>& samples)>& initDataGetter);
                ~AudioDevice();

                void start() final;
                void stop() final;

            private:
                void run();

                snd_pcm_t* playbackHandle = nullptr;
                snd_pcm_hw_params_t* hwParams = nullptr;
                snd_pcm_sw_params_t* swParams = nullptr;

                unsigned int periods = 4;
                snd_pcm_uframes_t periodSize = 1024;

                std::vector<uint8_t> data;

                std::atomic_bool running{false};
                Thread audioThread;
            };
        } // namespace alsa
    } // namespace audio
} // namespace ouzel

#endif

#endif // OUZEL_AUDIO_ALSAAUDIODEVICE_HPP
