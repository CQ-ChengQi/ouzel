// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_OSLAUDIODEVICE_HPP
#define OUZEL_AUDIO_OSLAUDIODEVICE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_OPENSL

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

#include "audio/AudioDevice.hpp"
#include "audio/opensl/OSLPointer.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace opensl
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

                void start() final;
                void stop() final;

                void enqueue(SLAndroidSimpleBufferQueueItf bufferQueue);

                inline auto getEngine() const noexcept { return engine; }

            private:
                Pointer<SLObjectItf> engineObject;
                SLEngineItf engine = nullptr;
                Pointer<SLObjectItf> outputMixObject;

                Pointer<SLObjectItf> playerObject;
                SLPlayItf player = nullptr;
                SLAndroidSimpleBufferQueueItf bufferQueue = nullptr;
                SLVolumeItf playerVolume = nullptr;

                std::vector<uint8_t> data;
            };
        } // namespace opensl
    } // namespace audio
} // namespace ouzel

#endif

#endif // OUZEL_AUDIO_OSLAUDIODEVICE_HPP
