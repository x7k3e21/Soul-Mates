
#include <stdint.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int32_t main(int32_t argc, char* argv[])
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        return EXIT_FAILURE;
    }

    SDL_Quit();
        
    return EXIT_SUCCESS;
}