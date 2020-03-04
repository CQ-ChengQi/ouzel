// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_WASAPIAUDIODEVICE_HPP
#define OUZEL_AUDIO_WASAPIAUDIODEVICE_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_WASAPI

#include <atomic>
#include <thread>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include "audio/AudioDevice.hpp"
#include "audio/wasapi/WASAPIPointer.hpp"
#include "utils/Thread.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace wasapi
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

                Pointer<IMMDeviceEnumerator> enumerator;
                Pointer<IMMDevice> device;
                Pointer<IMMNotificationClient> notificationClient;
                Pointer<IAudioClient> audioClient;
                Pointer<IAudioRenderClient> renderClient;
                HANDLE notifyEvent = nullptr;

                UINT32 bufferFrameCount;
                uint32_t sampleSize = 0;
                bool started = false;
                std::vector<uint8_t> data;

                std::atomic_bool running{false};
                Thread audioThread;
            };
        } // namespace wasapi
    } // namespace audio
} // namespace ouzel

#endif

#endif // OUZEL_AUDIO_WASAPIAUDIODEVICE_HPP
