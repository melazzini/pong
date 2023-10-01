#include "RendererBackendProvider.h"
#include "RendererPrimitiveSDL.h"
#include <SDL2/SDL.h>

SDL_Renderer *RendererBackendProvider::provideRendererSDL(RendererPrimitiveSDL *rendererPrimitive) const
{
    return rendererPrimitive->m_renderer.get();
}
