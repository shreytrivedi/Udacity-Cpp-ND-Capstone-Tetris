#ifndef I_RENDERER_H
#define I_RENDERER_H

#include "CommonDefs.h"
#include "Figure.h"
#include <string>

class IRenderer
{
public:
    virtual void Render(TetrisCanvas* canvas, BaseFigure* figure) = 0;
    virtual void UpdateWindowTitle(std::string title) = 0;
};
#endif