#include "BackendContextSDL.h"
#include "Events.h"

void EventManagerPrimitiveSDL::pollEvents(IEventManager &eventManager) const
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
        {
            eventManager.enqueueEvent(std::make_unique<EventQuit>());
        }
        else if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            eventManager.enqueueEvent(std::make_unique<EventQuit>());
        }

        if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RIGHT)
        {
            eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::RIGHT));
        }
        if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT)
        {
            eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::LEFT));
        }
        if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_UP)
        {
            eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::UP));
        }
        if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_DOWN)
        {
            eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::DOWN));
        }
    }
}

bool EventManagerPrimitiveSDL::isKeyPressed(Keyboard key) const
{
    auto keys = SDL_GetKeyboardState(nullptr);

    switch (key)
    {
    case Keyboard::A:
        return keys[SDL_SCANCODE_A];
        break;
    case Keyboard::B:
        return keys[SDL_SCANCODE_B];
        break;
    case Keyboard::C:
        return keys[SDL_SCANCODE_C];
        break;
    case Keyboard::D:
        return keys[SDL_SCANCODE_D];
        break;
    case Keyboard::E:
        return keys[SDL_SCANCODE_E];
        break;
    case Keyboard::F:
        return keys[SDL_SCANCODE_F];
        break;
    case Keyboard::G:
        return keys[SDL_SCANCODE_G];
        break;
    case Keyboard::H:
        return keys[SDL_SCANCODE_H];
        break;
    case Keyboard::I:
        return keys[SDL_SCANCODE_I];
        break;
    case Keyboard::J:
        return keys[SDL_SCANCODE_J];
        break;
    case Keyboard::K:
        return keys[SDL_SCANCODE_K];
        break;
    case Keyboard::L:
        return keys[SDL_SCANCODE_L];
        break;
    case Keyboard::M:
        return keys[SDL_SCANCODE_M];
        break;
    case Keyboard::N:
        return keys[SDL_SCANCODE_N];
        break;
    case Keyboard::O:
        return keys[SDL_SCANCODE_O];
        break;
    case Keyboard::P:
        return keys[SDL_SCANCODE_P];
        break;
    case Keyboard::Q:
        return keys[SDL_SCANCODE_Q];
        break;
    case Keyboard::R:
        return keys[SDL_SCANCODE_R];
        break;
    case Keyboard::S:
        return keys[SDL_SCANCODE_S];
        break;
    case Keyboard::T:
        return keys[SDL_SCANCODE_T];
        break;
    case Keyboard::U:
        return keys[SDL_SCANCODE_U];
        break;
    case Keyboard::V:
        return keys[SDL_SCANCODE_V];
        break;
    case Keyboard::W:
        return keys[SDL_SCANCODE_W];
        break;
    case Keyboard::X:
        return keys[SDL_SCANCODE_X];
        break;
    case Keyboard::Y:
        return keys[SDL_SCANCODE_Y];
        break;
    case Keyboard::Z:
        return keys[SDL_SCANCODE_Z];
        break;
    case Keyboard::RIGHT:
        return keys[SDL_SCANCODE_RIGHT];
        break;
    case Keyboard::LEFT:
        return keys[SDL_SCANCODE_LEFT];
        break;
    case Keyboard::UP:
        return keys[SDL_SCANCODE_UP];
        break;
    case Keyboard::DOWN:
        return keys[SDL_SCANCODE_DOWN];
        break;
    default:
        break;
    }
    throw std::runtime_error{"The given key doesn't exist in this backend!"};
}
