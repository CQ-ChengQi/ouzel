// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_XCODE_PBXREFERENCEPROXY_HPP
#define OUZEL_XCODE_PBXREFERENCEPROXY_HPP

#include "PBXFileReference.hpp"
#include "PBXContainerItemProxy.hpp"
#include "PBXSourceTree.hpp"
#include "storage/Path.hpp"

namespace ouzel
{
    namespace xcode
    {
        class PBXReferenceProxy final: public PBXFileReference
        {
        public:
            PBXReferenceProxy() = default;

            std::string getIsa() const override { return "PBXReferenceProxy"; }

            plist::Value encode() const override
            {
                auto result = PBXFileReference::encode();
                if (remoteRef) result["remoteRef"] = toString(remoteRef->getId());
                return result;
            }

            const PBXContainerItemProxy* remoteRef = nullptr;
        };
    }
}

#endif // OUZEL_XCODE_PBXREFERENCEPROXY_HPP
