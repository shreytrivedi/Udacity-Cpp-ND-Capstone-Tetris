#ifndef SDL_CONTROLLER_H
#define SDL_CONTROLLER_H

#include "SDL.h"
#include "Figure.h"
#include "IController.h"
#include "ITetrisControllerHost.h"

/**
 * SDLController: Controller that takes and processes inputs from the
 * user using the SDL libbrary. It implements the IController interface. 
 */
class SDLController : public IController
{
public:

    //Implementation of IController interface.

    /**
     * Polls the input event queue and checks for the interesting key events.
     * Based on the event type, callbacks are called on the TetrisGame.
     * To abstract out the TetrisGame from the Contoroller, the callbacks are 
     * called via the ITetrisControllerHost interrface implemented by the TetrisGame.
     */
    virtual void HandleInput(ITetrisControllerHost* host) override;
    virtual bool IsDownArrowPressed() override;
};

#endif