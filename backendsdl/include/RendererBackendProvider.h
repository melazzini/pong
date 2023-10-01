#pragma once

struct SDL_Renderer;
struct RendererPrimitiveSDL;

struct RendererBackendProvider
{
    SDL_Renderer *provideRendererSDL(RendererPrimitiveSDL *rendererPrimitive) const;
};
