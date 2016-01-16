// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "RenderTarget.h"

namespace ouzel
{
    class RendererD3D11;

    class RenderTargetD3D11: public RenderTarget
    {
        friend RendererD3D11;
    public:
        virtual ~RenderTargetD3D11();

        virtual bool init(Size2 const& size, bool depthBuffer);

    protected:
        RenderTargetD3D11();
    };
}
