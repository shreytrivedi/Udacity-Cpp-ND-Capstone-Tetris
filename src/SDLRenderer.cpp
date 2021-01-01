#include "SDLRenderer.h"
#include <iostream>

SDLRenderer::SDLRenderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height)
        : mScreenWidth(screen_width)
        , mScreenHeight(screen_height)
        , mGridWidth(grid_width)
        , mGridHeight(grid_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void SDLRenderer::Render(TetrisCanvas* canvas, BaseFigure* figure)
{
    TetrisCell cell;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    //Render gameArea
    SDL_Rect gameArea;
    //gameArea.w = kGridColumns * kScreenWidth/kGridWidth;
    //gameArea.h = kGridRows * kScreenHeight/kGridHeight;
    gameArea.w = kGridColumns *kMagnificationFactor;
    gameArea.h = kGridRows * kMagnificationFactor;
    gameArea.x = 0;
    gameArea.y = 0;    
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &gameArea);

    if(!canvas)
    {
        std::cout<<"\nCanvas is invalid";
        return;
    }

    //lets draw the canvas
    for(std::size_t i=0;i<kGridRows;i++)
    {
        for(std::size_t j=0;j<kGridColumns;j++)
        {
            if((*canvas)[i][j] == 0)
                continue;
            
            cell.po.x = j;
            cell.po.y = i;
            cell.Render(sdl_renderer);
        }
    }

    //lets draw the figure
    if(figure)
    {
        std::vector<Point> p = figure->GetPoints();
        for(std::size_t i=0;i<p.size();i++)
        {
            cell.po.x = p[i].x;
            cell.po.y = p[i].y;
            cell.Render(sdl_renderer);
        }
    }
    
    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void SDLRenderer::UpdateWindowTitle(std::string content)
{
    std::string title {content};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDLRenderer::~SDLRenderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

//Move and Assignment
SDLRenderer::SDLRenderer(SDLRenderer&& src)
{
    this->mGridHeight = src.mGridHeight;
    this->mGridWidth = src.mGridWidth;
    this->mScreenHeight = src.mScreenHeight;
    this->mScreenWidth = src.mScreenWidth;

    // Copy Window pointer
    this->sdl_window = src.sdl_window;

    // Copy renderer pointer
    this->sdl_renderer = src.sdl_renderer;
}

SDLRenderer& SDLRenderer::operator= (SDLRenderer&& src)
{
    if(this == &src)
        return *this;
    
    this->mGridHeight = src.mGridHeight;
    this->mGridWidth = src.mGridWidth;
    this->mScreenHeight = src.mScreenHeight;
    this->mScreenWidth = src.mScreenWidth;

    SDL_DestroyWindow(this->sdl_window);

    // Copy Window pointer
    this->sdl_window = src.sdl_window;

    // Copy renderer pointer
    this->sdl_renderer = src.sdl_renderer;

    return *this;
}