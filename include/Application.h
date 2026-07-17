
#pragma once

#include <stdint.h>

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <SDL3/SDL_events.h>

#include <string>

namespace game
{
    class Application
    {
        public:

        void execute();

        bool initialize();
        void shutdown();

        void loop();

        private:

        ::SDL_Window* m_Window;
        ::SDL_Renderer* m_Renderer;

        ::SDL_WindowFlags m_WindowFlags = 0;

        ::std::string m_WindowTitle = "Soul Mates";

        ::int32_t m_WindowWidth = 800;
        ::int32_t m_WindowHeight = 600;

        bool m_IsRunning = true;
    };
}