// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_MIXER_OBJECT_HPP
#define OUZEL_AUDIO_MIXER_OBJECT_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include "audio/mixer/Source.hpp"
#include "math/Quaternion.hpp"
#include "math/Vector.hpp"

namespace ouzel
{
    namespace audio
    {
        namespace mixer
        {
            class Object
            {
            public:
                Object() noexcept = default;
                explicit Object(std::unique_ptr<Source> initSource) noexcept:
                    source(std::move(initSource))
                {
                }

                virtual ~Object()
                {
                    if (parent)
                        parent->removeChild(*this);
                }

                Object(const Object&) = delete;
                Object& operator=(const Object&) = delete;

                Object(Object&&) = delete;
                Object& operator=(Object&&) = delete;

                void addChild(Object& child)
                {
                    if (child.parent != this)
                    {
                        if (child.parent)
                            child.parent->removeChild(child);

                        auto i = std::find(children.begin(), children.end(), &child);
                        if (i == children.end())
                        {
                            child.parent = this;
                            children.push_back(&child);
                        }
                    }
                }

                void removeChild(Object& child)
                {
                    if (child.parent == this)
                    {
                        auto i = std::find(children.begin(), children.end(), &child);
                        if (i != children.end())
                        {
                            child.parent = this;
                            children.erase(i);
                        }
                    }
                }

                void play()
                {
                    if (source)
                        source->play();
                }

                void stop(bool reset)
                {
                    if (source)
                        source->stop(reset);
                }

                // TODO: make non-virtual
                virtual void getSamples(uint32_t frames, uint32_t channels, uint32_t sampleRate, std::vector<float>& samples)
                {
                    for (auto child : children)
                        child->getSamples(frames, channels, sampleRate, samples);

                    if (source)
                        source->getSamples(frames, channels, sampleRate, samples);
                }

            protected:
                Object* parent = nullptr;
                std::vector<Object*> children;
                std::unique_ptr<Source> source;
            };
        }
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_MIXER_OBJECT_HPP
