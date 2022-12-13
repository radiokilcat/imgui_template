#include "Application.hpp"

#include "Application.hpp"
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>
#include <imgui.h>

namespace App {

    Application::Application() {
        unsigned int init_flags{
                SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER
        };
        if (SDL_Init(init_flags) != 0) {
//            APP_ERROR("Error: %s\n", SDL_GetError());
            m_exit_status = 1;
        }

        // Create new window with the title "Application".
        m_window = std::make_unique<Window>(
                Window::Settings{"Application"}
        );
    }

    Application::~Application() {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_Quit();
    }

    int App::Application::run() {
        if (m_exit_status == 1) {
            return m_exit_status;
        }
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io{ImGui::GetIO()};

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        // Enable docking
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        const float font_scaling_factor{m_window->get_scale()};
        const float font_size{18.0F * font_scaling_factor};

        //Load font and set as default with proper scaling
        io.Fonts->AddFontFromFileTTF(
                "fonts/Manrope.ttf",
                font_size);
        io.FontDefault = io.Fonts->AddFontFromFileTTF(
                "fonts/Manrope.ttf",
                font_size);
        io.FontGlobalScale = 1.0F / font_scaling_factor;

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(
          m_window->get_native_window(),
          m_window->get_native_renderer()
        );
        ImGui_ImplSDLRenderer_Init(
          m_window->get_native_renderer()
        );
        m_running = true;
        while (m_running) {
            // Poll SDL events
            SDL_Event event{};
            while (SDL_PollEvent(&event) == 1) {
              ImGui_ImplSDL2_ProcessEvent(&event);
              // Listen for the quit event to stop the application
              if (event.type == SDL_QUIT) {
                stop();
              }
              // Capture events inside the window
              if (event.type == SDL_WINDOWEVENT &&
                  event.window.windowID == SDL_GetWindowID(m_window->get_native_window()))
              {
                  on_event(event.window);
              }
            }

            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            if (!m_minimized)
            {
                ImGui::DockSpaceOverViewport();
                if (ImGui::BeginMainMenuBar())
                {
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("Exit"))
                        {
                            stop();
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("View"))
                    {
                        ImGui::MenuItem("Some Panel",
                                        nullptr,
                                        &m_show_some_panel);
                        ImGui::EndMenu();
                    }
               ImGui::EndMainMenuBar();
               }

                if (m_show_some_panel) {
                    ImGui::Begin("Some panel", &m_show_some_panel);
                    ImGui::Text("Hello World");
                    ImGui::End();
                }
            }

            ImGui::Render();

            SDL_SetRenderDrawColor(
                    m_window->get_native_renderer(),
                    // Gray clear color (rgba)
                    100, 100, 100, 255
            );
            SDL_RenderClear(m_window->get_native_renderer());
            ImGui_ImplSDLRenderer_RenderDrawData(
                    ImGui::GetDrawData()
            );
            SDL_RenderPresent(
                    m_window->get_native_renderer()
            );
        }
        return m_exit_status;
    }

    void App::Application::stop() {
        m_running = false;
    }

    void Application::on_event(const SDL_WindowEvent &event) {
        switch (event.event) {
            case SDL_WINDOWEVENT_CLOSE:
                return on_close();
            case SDL_WINDOWEVENT_MINIMIZED:
                return on_minimize();
            case SDL_WINDOWEVENT_SHOWN:
                return on_shown();
        }
    }

void Application::on_close()
{
    stop();
}

void Application::on_shown()
{
    m_minimized = false;
}

void Application::on_minimize()
{
    m_minimized = true;
}

}  // namespace App