#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <iostream>
#include <memory>
#include "IRenderer.h"
#include "IController.h"
#include "ITetrisHost.h"
#include "FigureFactory.h"
#include "Figure.h"
#include "ITetrisControllerHost.h"

/**
 * This shoudlnt be here. Included just to use the timing utilities
 * In the future, <chrono> should be used.
 */
#include "SDL.h"

class TetrisGame : public ITetrisHost, public ITetrisControllerHost
{
public:

    static TetrisGame* CreateGame(IController* controller, IRenderer* renderer, std::size_t frameDuration, 
                                    std::size_t gridRows, std::size_t gridColumns)
    {
        static TetrisGame game(controller, renderer, frameDuration, gridRows, gridColumns);
        return &game;
    }

    /**
     * 
     * Given a figure's coordinates, it validate that the figure
     * is in a valid empty space of the canvas within the 
     * boundaries
     * 
     * Input:
     * @points referene to a vector of Points that representsa Figure
     * 
     * Output:
     * bool returns true if the figure is in a valid space of the canvas and false otherwise
    
     */
    bool ValidatePoint(const std::vector<Point>& points);


    /**
     * This containns the main gme loop
     * Calls the controller to handle input, modifies the game model
     * and calls the renderer with the updated game model
     */
    void Run();

    //Overrides for ITetrisControllerHost
    virtual void OnUpArrowPressed() override;
    virtual void OnDownArrowPressed() override;
    virtual void OnLeftArrowPressed() override;
    virtual void OnRightArrowPressed() override;

    virtual void OnSpaceBarPressed() override 
    { 
        mGameRunning = (mGameRunning==true) ? false:true;
        if(!mGameRunning)
             mRenderer->UpdateWindowTitle("Game Paused");
        else
             mRenderer->UpdateWindowTitle(" Score:" + std::to_string(mScore));
    }

    virtual void OnQuit() override
    {
        mGameQuitting = true;
    }

private:

    TetrisGame(IController* controller, IRenderer* renderer, std::size_t frameDuration,
                std::size_t gridRows = 20, std::size_t gridColumns = 10) 
        : mRows(gridRows)
        , mColumns(gridColumns)
        , mController(controller)
        , mRenderer(renderer)
        , mGameQuitting(false)
        , mGameRunning(true)
        , mEngine(dev())
        , mWidthSampleSpace(0, static_cast<int>(gridColumns) - 1)
        , mScore(0)
    {
        msptrTetrisCanvas = std::make_unique<TetrisCanvas>(mRows, std::vector<int>(mColumns));
        msptrFigureFactory = std::make_unique<FigureFactory>(7);
    }

    /**
     * Checks the TetrisCanvas if any row is full and updates the Canvas accordingly.
     */
    void CheckForCompleteLines();

    /**
     * Responsible for updating the score with the appropriate formula.
     * 
     * The formula is as follows:
     * - Add 10 points for every Row completed.
     * - Add 30 bonus points for every 3 consecutive rows completed/erased.
     * - Add 40 bonus points for every 4 consecutive rows completed/erased.
     * 
     * Input:
     * @rowsErased number of rows completed/erased
     * @consRows number of consecutive rows completed.
     */
    void UpdateScore(int rowsErased, int consRows);

    /**
     * Responsible for randomizing a figure's lateral start position.
     * If no such location can be found, for now we assume that the figure 
     * can no longer be placed and hence we initiate a game over.
     */
    bool RandomizeFigureDropLocation();

    /**
     * Responsible for Initiating the game obver logic.
     * Here we set mGameRunning to false and update the WindowTitle to GameOver.
     */
    void InitiateGameOver();

    unsigned int     mScore;
    bool             mGameQuitting;
    bool             mGameRunning;
    std::size_t      mRows;
    std::size_t      mColumns;
    IController*     mController;
    IRenderer*       mRenderer;

    std::unique_ptr<TetrisCanvas>   msptrTetrisCanvas;
    std::unique_ptr<FigureFactory>  msptrFigureFactory;    //Used for generating the Figures
    std::unique_ptr<BaseFigure>     mCurrFigure;

    std::random_device dev;
    std::mt19937       mEngine;
    std::uniform_int_distribution<int> mWidthSampleSpace;
    
};

#endif