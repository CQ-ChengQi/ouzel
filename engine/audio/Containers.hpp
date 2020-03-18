// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_CONTAINERS_HPP
#define OUZEL_AUDIO_CONTAINERS_HPP

#include <algorithm>
#include <vector>
#include "audio/Source.hpp"

namespace ouzel
{
    namespace audio
    {
        class Container: public Source
        {
        public:
        };

        class Parallel final: public Container
        {
        public:
            void getSamples(std::uint32_t frames, std::uint32_t channels, std::uint32_t sampleRate, std::vector<float>& samples) override
            {
            }
        };

        class Random final: public Container
        {
        public:
            void getSamples(std::uint32_t frames, std::uint32_t channels, std::uint32_t sampleRate, std::vector<float>& samples) override
            {
            }
        };

        class Sequence final: public Container
        {
        public:
            void getSamples(std::uint32_t frames, std::uint32_t channels, std::uint32_t sampleRate, std::vector<float>& samples) override
            {
            }
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_CONTAINERS_HPP
