// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_MIXER_MIXER_HPP
#define OUZEL_AUDIO_MIXER_MIXER_HPP

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include "audio/mixer/Commands.hpp"
#include "audio/mixer/Object.hpp"
#include "audio/mixer/Processor.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace mixer
        {
            class Mixer
            {
            public:
                class Event
                {
                public:
                    enum class Type
                    {
                        STREAM_STARTED,
                        STREAM_RESET,
                        STREAM_STOPPED,
                        STARVATION
                    };

                    Event() {}
                    explicit Event(Type initType): type(initType) {}

                    Type type;
                    uintptr_t objectId;
                };

                Mixer(uint32_t initBufferSize,
                      uint16_t initChannels,
                      const std::function<void(const Event&)>& initCallback);

                Mixer(const Mixer&) = delete;
                Mixer& operator=(const Mixer&) = delete;

                Mixer(Mixer&&) = delete;
                Mixer& operator=(Mixer&&) = delete;

                void process();
                void getData(uint32_t frames, uint16_t channels, uint32_t sampleRate, std::vector<float>& samples);

                uintptr_t getObjectId()
                {
                    auto i = deletedObjectIds.begin();

                    if (i == deletedObjectIds.end())
                        return ++lastObjectId; // zero is reserved for null node
                    else
                    {
                        uintptr_t objectId = *i;
                        deletedObjectIds.erase(i);
                        return objectId;
                    }
                }

                void deleteObjectId(uintptr_t objectId)
                {
                    deletedObjectIds.insert(objectId);
                }

                void submitCommandBuffer(CommandBuffer&& commandBuffer)
                {
                    std::unique_lock<std::mutex> lock(commandQueueMutex);
                    commandQueue.push(std::forward<CommandBuffer>(commandBuffer));
                    lock.unlock();
                }
                
            private:
                void main();

                uint32_t bufferSize;
                uint16_t channels;
                std::function<void(const Event&)> callback;

                uintptr_t lastObjectId = 0;
                std::set<uintptr_t> deletedObjectIds;

                std::vector<std::unique_ptr<Object>> objects;

                Bus* masterBus = nullptr;

                std::thread mixerThread;

                class Buffer
                {
                public:
                    bool canRead() const { return frames > 0; }
                    bool canWrite() const { return frames < maxFrames; }

                    size_t frames = 0;
                    size_t maxFrames = 0;
                    size_t readPosition = 0;
                    size_t writePosition = 0;
                    std::vector<float> buffer;
                };

                std::mutex bufferMutex;
                std::condition_variable bufferCondition;
                Buffer buffer;

                std::queue<CommandBuffer> commandQueue;
                std::mutex commandQueueMutex;
            };
        }
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_MIXER_MIXER_HPP
