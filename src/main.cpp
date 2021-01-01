#include "CommonDefs.h"
#include "TetrisGame.h"
#include "SDLRenderer.h"
#include "SDLController.h"

int main()
{
  std::unique_ptr<SDLRenderer> sptrRenderer = std::make_unique<SDLRenderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::unique_ptr<SDLController> sptrController = std::make_unique<SDLController>();

  auto game = TetrisGame::CreateGame(sptrController.get(), sptrRenderer.get(), kMsPerFrame, kGridRows, kGridColumns);
  if(game)
    game->Run();

  std::cout<<"\nTetris Game is being shutdown";
  return 0;
}