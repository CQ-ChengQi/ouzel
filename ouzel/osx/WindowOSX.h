// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "Window.h"

#ifdef __OBJC__
@class NSWindow;
typedef NSWindow* NSWindowPtr;
@class OpenGLView;
typedef OpenGLView* OpenGLViewPtr;
#else
#include <objc/objc.h>
typedef id NSWindowPtr;
typedef id OpenGLViewPtr;
#endif

namespace ouzel
{
    class WindowOSX: public Window
    {
        friend Engine;
    public:
        virtual ~WindowOSX();
        
        virtual void close() override;
        
        virtual void setSize(const Size2& size) override;
        virtual void setFullscreen(bool fullscreen) override;
        virtual void setTitle(const std::string& title) override;
        
        void handleResize();
        void handleDisplayChange();
        void handleClose();
        void handleFullscreenChange(bool fullscreen);
        
    protected:
        WindowOSX(const Size2& size, bool resizable, bool fullscreen, const std::string& title);
        virtual bool init() override;
        
        NSWindowPtr _window = Nil;
        OpenGLViewPtr _openGLView = Nil;
    };
}
