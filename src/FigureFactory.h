#ifndef FIGURE_GEN_H
#define FIGURE_GEN_H

#include <random>
#include <memory>

#include "ITetrisHost.h"
#include "Figure.h"

/**
 * Factory to generate figures for the Tetris Game.
 */
class FigureFactory
{
public:

    FigureFactory(int typesOfFigures);
    std::unique_ptr<BaseFigure> GetNextFigure(ITetrisHost *host);


private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> figureSampleSpace;
};

#endif