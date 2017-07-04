// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace ouzel
{
    namespace audio
    {
        class Audio;
        class Stream;

        class SoundData
        {
            friend Audio;
        public:
            SoundData();
            virtual ~SoundData();

            virtual std::unique_ptr<Stream> createStream() = 0;
            virtual const std::vector<uint8_t>& getData() = 0;
            virtual std::vector<uint8_t> getData(Stream* stream, uint32_t size) = 0;

            uint16_t getFormatTag() const { return formatTag; }
            uint16_t getChannels() const { return channels; }
            uint32_t getSamplesPerSecond() const { return samplesPerSecond; }

        protected:
            uint16_t formatTag = 0;
            uint16_t channels = 0;
            uint32_t samplesPerSecond = 0;
        };
    } // namespace audio
} // namespace ouzel
