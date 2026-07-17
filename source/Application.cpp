
#include "Application.h"

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
}