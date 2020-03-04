// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#include "GltfLoader.hpp"
#include "Bundle.hpp"
#include "scene/SkinnedMeshRenderer.hpp"
#include "utils/Json.hpp"

namespace ouzel
{
    namespace assets
    {
        GltfLoader::GltfLoader(Cache& initCache):
            Loader(initCache, Loader::SkinnedMesh)
        {
        }

        bool GltfLoader::loadAsset(Bundle& bundle,
                                   const std::string& name,
                                   const std::vector<uint8_t>& data,
                                   bool mipmaps)
        {
            const json::Data d(data);

            const json::Value& nodesValue = d["nodes"];
            const json::Value& meshesValue = d["meshes"];

            scene::SkinnedMeshData skinnedMeshData;
            bundle.setSkinnedMeshData(name, std::move(skinnedMeshData));

            return true;
        }
    } // namespace assets
} // namespace ouzel
