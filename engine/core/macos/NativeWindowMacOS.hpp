// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_CORE_NATIVEWINDOWMACOS_HPP
#define OUZEL_CORE_NATIVEWINDOWMACOS_HPP

#include <CoreGraphics/CGGeometry.h>

#if defined(__OBJC__)
#  import <Cocoa/Cocoa.h>
#  import <CoreGraphics/CoreGraphics.h>
typedef NSWindow* NSWindowPtr;
typedef NSView* NSViewPtr;
typedef id<NSWindowDelegate> NSWindowDelegatePtr;
typedef NSScreen* NSScreenPtr;
#else
#  include <objc/NSObjCRuntime.h>
typedef id NSWindowPtr;
typedef id NSViewPtr;
typedef id NSWindowDelegatePtr;
typedef id NSScreenPtr;
typedef uint32_t CGDirectDisplayID;
#endif

#include "core/NativeWindow.hpp"
#include "graphics/Renderer.hpp"

namespace ouzel
{
    class NativeWindowMacOS final: public NativeWindow
    {
    public:
        NativeWindowMacOS(const std::function<void(const Event&)>& initCallback,
                          const Size2U& newSize,
                          bool newResizable,
                          bool newFullscreen,
                          bool newExclusiveFullscreen,
                          const std::string& newTitle,
                          graphics::Driver graphicsDriver,
                          bool newHighDpi);
        ~NativeWindowMacOS();

        void executeCommand(const Command& command) final;

        void close();

        void setSize(const Size2U& newSize);
        void setFullscreen(bool newFullscreen);
        void setTitle(const std::string& newTitle);
        void bringToFront();
        void show();
        void hide();
        void minimize();
        void maximize();
        void restore();

        void handleResize();
        void handleClose();
        void handleMinituarize();
        void handleDeminituarize();
        void handleFullscreenChange(bool newFullscreen);
        void handleScaleFactorChange();
        void handleScreenChange();
        void handleBecomeKeyChange();
        void handleResignKeyChange();

        inline auto getNativeWindow() const noexcept { return window; }
        inline auto getNativeView() const noexcept { return view; }
        inline auto getScreen() const noexcept { return screen; }
        inline auto getDisplayId() const noexcept { return displayId; }

    private:
        NSWindowPtr window = nil;
        NSViewPtr view = nil;
        NSWindowDelegatePtr windowDelegate = nil;
        NSScreenPtr screen = nil;
        CGDirectDisplayID displayId = 0;
        NSUInteger windowStyleMask = 0;
        CGRect windowRect;
    };
}

#endif // OUZEL_CORE_NATIVEWINDOWMACOS_HPP
