#ifndef FIGURE_H
#define FIGURE_H

#include "CommonDefs.h"
#include "ITetrisHost.h"
#include <cstddef>

/**
 * The BaseFigure class encapuslated all functionality and data 
 * common to all figures.
 * Each figure inherits from this class and initializes with
 * its own layout.
 * 
 * The following was referred to understand the layout of pieces and the rotation logic:
 * https://www.youtube.com/watch?v=zH_omFPqMO4
 * 
 */
class BaseFigure
{
public:

    BaseFigure(ITetrisHost* host) : mTetrisHost(host)
    {

    }

    /**
     * Move the figure to the right by dx units.
     * Amount should be positive in this case assuming origin (0,0)
     * is at the Top Left of the window.
     * 
     * Default to  1 unit;
     */
    bool MoveRight(int dx=1);

    /**
     * Move the figure to the left by dx units.
     * Amount should be negative in this case assuming origin (0,0)
     * is at the Top Left of the window.
     * 
     * Default to  1 unit;
     */
    bool MoveLeft(int dx=-1);

    /**
     * Move the figure down by dy units.
     * Amount should be positive in this case assuming origin (0,0)
     * is at the Top Left of the window.
     * 
     * Default to  1 unit;
     */
    bool MoveDown(int dy=1);

    /**
     * Rotate the figure by 90 degrees clockwise.
     * Amount should be negative in this case assuming origin (0,0)
     * is at the Top Left of the window.
     */
    bool Rotate();
    
    std::vector<Point>& GetPoints() { return p; }

    //statics
    std::size_t sGridRows;
    std::size_t sGridColumns;

protected:

    /**
     * Convert the layout of the figure to cartesian co-ordinates system.
     */
    static void GetFigureCoordinates(const int *figMap, std::vector<Point>& coords)
    {
        for(int i=0;i<4;i++)
        {
            Point temp;
            temp.x = figMap[i] % 2;
            temp.y = figMap[i] / 2;
            coords.push_back(temp);
        }

    }
    
    std::vector<Point> p;
    ITetrisHost* mTetrisHost;

private:

    /**
     * Move the figure laterally along the X-Axis by dx units.
     * Amount should be positive moving right and negative while moving left assuming origin (0,0)
     * is at the Top Left of the window.
     * 
     * Default to  1 unit;
     */
    bool MoveLaterally(int dx);
};


/**
 * Macro to generate the Concrete Figure classes.
 * 
 * It will expand as follows:
 * 
 * class FigureT : public BaseFigure
 * {
 * public:
 *
 *   FigureT(ITetrisHost* host) : BaseFigure(host)
 *   {
 *       GetFigureCoordinates(figMap, p);
 *   }
 *
 * private:
 *   const int figMap[4] = {3, 5, 4, 7};
 * };
 */

#define FIGURE_DEF(name, a, b, c, d)               \
    class name : public BaseFigure                 \
    {                                              \
    public:                                        \
        name(ITetrisHost* host) : BaseFigure(host) \
        {                                          \
            GetFigureCoordinates(figMap, p);       \
        }                                          \
                                                   \
    private:                                       \
        const int figMap[4] = {a, b, c, d};        \
    };                                             \

/**
 *    _
 *  _|_|
 * |_|_|
 *   |_|
 * 
 */

FIGURE_DEF(FigureT, 3, 5, 4, 7)

/**
 *    _
 *   |_|
 *   |_|
 *   |_|
 *   |_|
 */
FIGURE_DEF(FigureI, 1, 3, 5, 7)

/**
 *    _
 *   |_|_
 *   |_|_|
 *     |_|
 *   
 */
FIGURE_DEF(FigureS, 2, 4, 5, 7)

/**
 *    _ _
 *   |_|_|
 *   |_|_|
 *   
 */
FIGURE_DEF(FigureO, 2, 3, 4, 5)


/**
 *     _
 *   _|_|
 *  |_|_|
 *  |_|
 *   
 */
FIGURE_DEF(FigureZ, 3, 5, 4, 6)

/**
 *   _
 *  |_|
 *  |_|_
 *  |_|_|
 *   
 */
FIGURE_DEF(FigureL, 2, 4, 6, 7)

/**
 *     _
 *    |_|
 *   _|_|
 *  |_|_|
 *   
 */
FIGURE_DEF(FigureJ, 3, 5, 7, 6)


#endif