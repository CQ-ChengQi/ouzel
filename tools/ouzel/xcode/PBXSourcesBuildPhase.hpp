// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_XCODE_PBXSOURCESBUILDPHASE_HPP
#define OUZEL_XCODE_PBXSOURCESBUILDPHASE_HPP

#include <vector>
#include "PBXBuildPhase.hpp"
#include "PBXBuildFile.hpp"

namespace ouzel
{
    namespace xcode
    {
        class PBXSourcesBuildPhase final: public PBXBuildPhase
        {
        public:
            PBXSourcesBuildPhase() = default;

            std::string getIsa() const override { return "PBXSourcesBuildPhase"; }

            plist::Value encode() const override
            {
                auto result = PBXBuildPhase::encode();
                result["files"] = plist::Value::Array{};
                for (auto file : files)
                    if (file) result["files"].pushBack(toString(file->getId()));

                return result;
            }

            std::vector<const PBXBuildFile*> files;
        };
    }
}

#endif // OUZEL_XCODE_PBXSOURCESBUILDPHASE_HPP
