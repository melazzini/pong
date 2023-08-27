#include "../include/BackendContextSDL.h"
#include <iostream>

BackendContextSDL *BackendContextSDL::getInstance()
{
    static BackendContextSDL backend{};
    return &backend;
}

BackendContextSDL::BackendContextSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        abort();
    }
}
