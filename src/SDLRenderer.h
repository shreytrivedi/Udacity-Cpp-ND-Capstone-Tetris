#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include "CommonDefs.h"
#include "IRenderer.h"
#include "SDL.h"
//#include "SDL_ttf.h"

/**
 * This class is solely responsible for drawing every cell in Tetris Game.
 * 
 * A cell is as follows:
 * 
 *      (0,0)    1 unit width
 *         ________________________
 *        | (0.2, 0.2)             |  
 *        |   _________________    |
 *        |  |.................|   |
 *        |  |.................|   |
 *        |  |.................|   | 1 unit height
 *        |  |.................|   |
 *        |  |.................|   |
 *        |  |.................|   |
 *        | 0.6 unit width & height| 
 *        |________________________|
 *                                   (1,1)
 */
class TetrisCell
{
public:
  SDL_Point po;

  void Render(SDL_Renderer* sdl_renderer)
  {
    SDL_Rect outerRect;
    //outerRect.w = kScreenWidth/kGridWidth; kMagnificationFactor
    //outerRect.h = kScreenHeight/kGridHeight;
    outerRect.w = kMagnificationFactor;
    outerRect.h = kMagnificationFactor;
    outerRect.x = po.x * outerRect.w;
    outerRect.y = po.y * outerRect.h;    
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &outerRect);

    SDL_Rect innerRect;
    //innerRect.w = 0.6 * kScreenWidth/kGridWidth;  //60%
    //innerRect.h = 0.6 * kScreenHeight/kGridHeight; //60%
    innerRect.w = 0.6 * kMagnificationFactor;  //60%
    innerRect.h = 0.6 * kMagnificationFactor; //60%
    //innerRect.x = (po.x + 0.2) * kScreenHeight/kGridHeight;
    //innerRect.y = (po.y + 0.2) * kScreenHeight/kGridHeight;  
    innerRect.x = (po.x + 0.2) * kMagnificationFactor;
    innerRect.y = (po.y + 0.2) * kMagnificationFactor;  
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &innerRect);
  }

};

/**
 * SDL Renderer: It uses the SDL Library to draw the objects on the screen
 * It implements the functionalities in the IRenderer interface.
 * TetrisGame never gets to see the SDLRenderer as it is abstracted behind IRenderer.
 */
class SDLRenderer : public IRenderer
{
public:
    SDLRenderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
    
   ~SDLRenderer();

    //Copy and Assignment Deleted.
    SDLRenderer(const SDLRenderer& src) = delete;
    SDLRenderer& operator= (const SDLRenderer& src) = delete;

    //Move and Assignment
    SDLRenderer(SDLRenderer&& src);
    SDLRenderer& operator= (SDLRenderer&& src);

    /**
     * Implementations of the IRenderer interface.
     */
    virtual void Render(TetrisCanvas* canvas, BaseFigure* figure) override;
    virtual void UpdateWindowTitle(std::string title) override;

  
private:

    SDL_Window        *sdl_window;
    SDL_Renderer      *sdl_renderer;

    std::size_t mScreenWidth;
    std::size_t mScreenHeight;
    std::size_t mGridWidth;
    std::size_t mGridHeight;
};
#endif