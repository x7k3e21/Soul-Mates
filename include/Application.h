
#pragma once

#include <stdint.h>

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <SDL3/SDL_events.h>

#define SOL_ALL_SAFETIES_ON 1

#include <sol/state.hpp>

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

        // TODO:
        // bool initializeSDL();
        // bool initializeLua();

        void handleWindowEvents(const ::SDL_WindowEvent& event);

        // TODO:
        // void handleKeyboardEvents(const ::SDL_KeyboardEvent& event);

        ::SDL_Window* m_Window;
        ::SDL_Renderer* m_Renderer;

        ::SDL_WindowFlags m_WindowFlags = 0;

        ::std::string m_WindowTitle = "Soul Mates";

        ::int32_t m_WindowWidth = 800;
        ::int32_t m_WindowHeight = 600;

        // TODO: create separate Window class with state handling
        ::int32_t m_WindowPosX = 0;
        ::int32_t m_WindowPosY = 0;

        bool m_HasMouseFocus = false;
        bool m_HasKeyboardFocus = false;

        bool m_IsFullscreen = false;

        bool m_IsMinimized = false;

        ::sol::state m_LuaState;

        bool m_IsRunning = true;
    };
}