#ifndef I_TETRIS_CONTROLLER_HOST_H
#define I_TETRIS_CONTROLLER_HOST_H


/**
 * Represents a set of callbacks that the TetrisGame
 * will likely be interested in receiving from the controller.
 * 
 * The main is to abstract the details of the TetrisGame behind
 * behind this interface.
 */
class ITetrisControllerHost
{
public:
    virtual void OnUpArrowPressed() = 0;
    virtual void OnDownArrowPressed() = 0;
    virtual void OnLeftArrowPressed() = 0;
    virtual void OnRightArrowPressed() = 0;

    virtual void OnSpaceBarPressed() = 0;
    virtual void OnQuit() = 0;
};

#endif