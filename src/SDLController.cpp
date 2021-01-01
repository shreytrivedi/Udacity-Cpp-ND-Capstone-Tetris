#include "SDLController.h"

void SDLController::HandleInput(ITetrisControllerHost* host)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT) 
        {
          host->OnQuit();
        }
        else if(e.type == SDL_KEYDOWN)
        {
          switch(e.key.keysym.sym)
          {
          case SDLK_UP:
            host->OnUpArrowPressed();
            break;
          case SDLK_LEFT:
            host->OnLeftArrowPressed();
            break;
          case SDLK_RIGHT:
            host->OnRightArrowPressed();
            break;
          case SDLK_SPACE:
            host->OnSpaceBarPressed();
            break;
          }
        }
    }
}

bool SDLController::IsDownArrowPressed()
{
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  return (state[SDL_SCANCODE_DOWN] == 1);
}