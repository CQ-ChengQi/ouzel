// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_OALAUDIODEVICE_HPP
#define OUZEL_AUDIO_OALAUDIODEVICE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_OPENAL

#include <atomic>
#include <thread>

#if defined(__APPLE__)
#  include <OpenAl/al.h>
#  include <OpenAl/alc.h>
#else
#  include <AL/al.h>
#  include <AL/alc.h>
#endif

#include "audio/AudioDevice.hpp"
#include "utils/Thread.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace openal
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
                void process();

                inline auto getDevice() const noexcept { return device; }
                inline auto getContext() const noexcept { return context; }

            private:
                void run();

                ALCdevice* device = nullptr;
                ALCcontext* context = nullptr;

                ALenum format40 = 0;
                ALenum format51 = 0;
                ALenum format61 = 0;
                ALenum format71 = 0;

                ALuint sourceId = 0;
                ALenum format = 0;
                uint32_t nextBuffer = 0;
                ALuint bufferIds[2] = {0, 0};

                uint32_t sampleSize = 0;
                std::vector<uint8_t> data;

#if !defined(__EMSCRIPTEN__)
                std::atomic_bool running{false};
                Thread audioThread;
#endif
            };
        } // namespace openal
    } // namespace audio
} // namespace ouzel

#endif

#endif // OUZEL_AUDIO_OALAUDIODEVICE_HPP
