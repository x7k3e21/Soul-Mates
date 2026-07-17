
#include <stdint.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <SDL3/SDL_main.h>

#include "Application.h"

int32_t main(int32_t argc, char* argv[])
{
    game::Application application;
    application.execute();
    
    return EXIT_SUCCESS;
}