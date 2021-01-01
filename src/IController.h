#ifndef I_CONTROLLER_H
#define I_CONTROLLER_H

/**
 * Represents an interface for a Tetris Controller.
 * Platform specific implementations need to extend
 * this class and implement the functionality. 
 * 
 * The idea is to keep the TetrisGame platform agnostic
 */

class ITetrisControllerHost;

class IController
{
public:
    virtual void HandleInput(ITetrisControllerHost* host) = 0;
    virtual bool IsDownArrowPressed() = 0;
};
#endif