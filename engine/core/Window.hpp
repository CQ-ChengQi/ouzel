// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_CORE_WINDOW_HPP
#define OUZEL_CORE_WINDOW_HPP

#include <memory>
#include <string>
#include "core/NativeWindow.hpp"
#include "graphics/Renderer.hpp"
#include "math/Size.hpp"

namespace ouzel
{
    class Engine;

    class Window final
    {
    public:
        enum Flags
        {
            Resizable = 0x01,
            Fullscreen = 0x02,
            ExclusiveFullscreen = 0x04,
            HighDpi = 0x08,
            Depth = 0x10
        };

        enum class Mode
        {
            Windowed,
            WindowedFullscreen,
            Fullscreen
        };

        Window(Engine& initEngine,
               const Size2U& newSize,
               uint32_t flags,
               const std::string& newTitle,
               graphics::Driver graphicsDriver);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        inline auto getNativeWindow() const noexcept { return nativeWindow.get(); }

        void close();
        void update();

        inline auto& getSize() const noexcept { return size; }
        void setSize(const Size2U& newSize);

        inline auto& getResolution() const noexcept { return resolution; }

        inline auto isResizable() const noexcept { return resizable; }

        void setFullscreen(bool newFullscreen);
        inline auto isFullscreen() const noexcept { return fullscreen; }

        inline auto isExclusiveFullscreen() const noexcept { return exclusiveFullscreen; }

        inline auto& getTitle() const noexcept { return title; }
        void setTitle(const std::string& newTitle);
        void bringToFront();
        void show();
        void hide();
        void minimize();
        void maximize();
        void restore();

        inline auto isVisible() const noexcept { return visible; }
        inline auto isMinimized() const noexcept { return minimized; }

        inline auto convertWindowToNormalizedLocation(const Vector2F& position) const noexcept
        {
            return Vector2F(position.v[0] / size.v[0], position.v[1] / size.v[1]);
        }

        inline auto convertNormalizedToWindowLocation(const Vector2F& position) const noexcept
        {
            return Vector2F(position.v[0] * size.v[0], position.v[1] * size.v[1]);
        }

    private:
        void eventCallback(const NativeWindow::Event& event);
        void handleEvent(const NativeWindow::Event& event);

        Engine& engine;
        std::unique_ptr<NativeWindow> nativeWindow;

        Size2U size;
        Size2U resolution;
        bool resizable = false;
        bool fullscreen = false;
        bool exclusiveFullscreen = false;
        bool highDpi = true;
        bool visible = false;
        bool minimized = false;
        uint32_t displayId = 0;

        std::string title;

        std::mutex eventQueueMutex;
        std::queue<NativeWindow::Event> eventQueue;
    };
}

#endif // OUZEL_CORE_WINDOW_HPP
