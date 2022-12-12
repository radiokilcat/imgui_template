#pragma once

#include <SDL.h>
#include <memory>
#include "Window.hpp"

namespace App {

    class Application {
    public:
        Application();
        ~Application();

        void on_event(const SDL_WindowEvent& event);

        void on_minimize();
        void on_shown();
        void on_close();

        int run();
        void stop();

    private:
        int m_exit_status{0};
        bool m_running{true};
        bool m_minimized{false};

        // Hold reference to window.
        std::unique_ptr<Window> m_window{nullptr};

        bool m_show_some_panel{true};
    };

}
