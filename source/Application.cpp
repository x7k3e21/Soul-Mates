
#include "Application.h"

#include <iostream>

namespace game
{
    void Application::execute()
    {
        this->initialize();

        this->loop();

        this->shutdown();
    }

    bool Application::initialize()
    {
        if (::SDL_InitSubSystem(SDL_INIT_VIDEO) == false)
        {
            return false;
        }

        this->m_Window = ::SDL_CreateWindow(
            this->m_WindowTitle.c_str(),

            this->m_WindowWidth, 
            this->m_WindowHeight,

            this->m_WindowFlags
        );

        if(this->m_Window == nullptr)
        {
            return false;
        }

        this->m_Renderer = ::SDL_CreateRenderer(this->m_Window, nullptr);

        if(this->m_Renderer == nullptr)
        {
            return false;
        }

        ::SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        this->m_LuaState.open_libraries(
            ::sol::lib::base
        );

        return true;
    }

    void Application::shutdown()
    {
        if(this->m_Renderer != nullptr)
        {
            ::SDL_DestroyRenderer(this->m_Renderer);
            this->m_Renderer = nullptr;
        }

        if(this->m_Window != nullptr)
        {
            ::SDL_DestroyWindow(this->m_Window);
            this->m_Window = nullptr;
        }

        ::SDL_QuitSubSystem(SDL_INIT_VIDEO);

        ::SDL_Quit();
    }

    void Application::loop()
    {
        while(this->m_IsRunning == true)
        {
            ::SDL_Event event;
            while(::SDL_PollEvent(&event))
            {
                if(event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST)
                {
                    this->handleWindowEvents(event.window);
                }

                switch (event.type)
                {
                    case SDL_EVENT_QUIT:
                    {
                        this->m_IsRunning = false;
                        break;
                    }
                }
            }

            ::SDL_RenderClear(this->m_Renderer);

            ::SDL_RenderPresent(this->m_Renderer);
        }
    }

    // TODO: create separate Window class with state handling
    void Application::handleWindowEvents(const ::SDL_WindowEvent& event)
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_MOVED:
            {
                this->m_WindowPosX = event.data1;
                this->m_WindowPosY = event.data2;
                break;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                break;
            }

            case SDL_EVENT_WINDOW_MINIMIZED:
            {
                this->m_IsMinimized = true;
                break;
            }

            case SDL_EVENT_WINDOW_MAXIMIZED:
            {
                this->m_IsMinimized = false;
                break;
            }

            case SDL_EVENT_WINDOW_MOUSE_ENTER:
            {
                this->m_HasMouseFocus = true;
                break;
            }

            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
            {
                this->m_HasMouseFocus = false;
                break;
            }

            case SDL_EVENT_WINDOW_FOCUS_GAINED:
            {
                this->m_HasKeyboardFocus = true;
                break;
            }

            case SDL_EVENT_WINDOW_FOCUS_LOST:
            {
                this->m_HasKeyboardFocus = false;
                break;
            }

            case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
            {
                this->m_IsFullscreen = true;
                break;
            }

            case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
            {
                this->m_IsFullscreen = false;
                break;
            }
        }
    }
}