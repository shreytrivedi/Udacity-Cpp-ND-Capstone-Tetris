#include "TetrisGame.h"

#include <chrono>

using tp = std::chrono::system_clock::time_point;

void TetrisGame::Run()
{
    Uint32 frame_start, frame_end, frame_duration;

    // tp start = std::chrono::system_clock::now();
    // std::chrono::milliseconds delay(300);
    // std::chrono::duration<long int> timerInMs;

    mCurrFigure = msptrFigureFactory->GetNextFigure(this);
    
    Uint32 delay = 500;
    Uint32 timer = 0;
    Uint32 target_frame_duration = 1000 / 60;
    while(true)
    {
        delay = 500;
        //std::cout<<"\nSTDBG::Game Loop Running";
        //tp now = std::chrono::system_clock::now();
        //timerInMs += std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
        frame_start = SDL_GetTicks();

        mController->HandleInput(this);

        if(mGameQuitting)
            break;

        if(mGameRunning)
        {
            if(mController->IsDownArrowPressed())
                delay = 50; //50ms
            
            if(timer >= delay) 
            {
                //lets move the current figure down
                if(mCurrFigure)
                {

                    bool moveSucc = mCurrFigure->MoveDown(1);

                    if(!moveSucc) //The piece can't move further
                    {
                        std::vector<Point> p = mCurrFigure->GetPoints();

                        for(std::size_t i=0;i<p.size();i++)
                        {
                            if(p[i].y == 0)
                            {
                                InitiateGameOver();
                                continue;
                            }

                            (*msptrTetrisCanvas)[p[i].y][p[i].x] = 1;
                        }

                        CheckForCompleteLines();    

                        //lets release this figure andget a new one
                        mCurrFigure.release();
                        mCurrFigure = msptrFigureFactory->GetNextFigure(this);
                        if(!RandomizeFigureDropLocation())
                        {
                            InitiateGameOver();
                            //break;
                            continue;
                        }
                    }
                }
                
                timer = 0;
            }

            //lets render
            //mRenderer->Render(msptrTetrisCanvas.get(), mCurrFigure.get());
            mRenderer->UpdateWindowTitle(" Score:" + std::to_string(mScore));
        }

        mRenderer->Render(msptrTetrisCanvas.get(), mCurrFigure.get());

        frame_end = SDL_GetTicks();
        frame_duration = frame_end - frame_start;

        if (frame_duration < target_frame_duration)
        {
            //std::cout<<"\nSTDBG::Delaying by "<<target_frame_duration - frame_duration;
            SDL_Delay(target_frame_duration - frame_duration);
        }

        timer += SDL_GetTicks() - frame_start;
    }
}

bool TetrisGame::ValidatePoint(const std::vector<Point>& points)
{
    for(std::size_t i=0;i<points.size();i++)
    {
        if(points[i].y<0 || points[i].y>=kGridRows)
            return false;

        if(points[i].x<0 || points[i].x>=kGridColumns)
            return false;

        if((*msptrTetrisCanvas)[points[i].y][points[i].x]==1)
            return false;
    }

    return true;
}

void TetrisGame::CheckForCompleteLines()
{
    //Check from the last row. If any row is complete we will not copy it

    int last = kGridRows-1;
    int consRows = 0;
    int maxConsRows = 0;
    int rowsErased = 0;

    for(int i=kGridRows-1;i>=0;i--)
    {
        int count=0;

        for(int j=0;j<kGridColumns;j++)
        {
            if((*msptrTetrisCanvas)[i][j] == 1)
                count++;
        }

        if(count<kGridColumns)
        {
            (*msptrTetrisCanvas)[last] = (*msptrTetrisCanvas)[i];
            last--;
            consRows = 0;
        }
        else
        {
            rowsErased++;
            consRows++;
            maxConsRows = maxConsRows > consRows ? maxConsRows : consRows;
        }
    }

    if(rowsErased>0)
        std::cout<<"\nRows Erased:"<<rowsErased<<" consRows:"<<maxConsRows;
    UpdateScore(rowsErased, maxConsRows);
}

void TetrisGame::UpdateScore(int rowsErased, int consRows)
{
    //Add 10 points for every row eliminated;
    mScore += kScorePerRowErased * rowsErased;
    if(consRows >= 3)
    {
        //Add a bonus of 10 points per row
        mScore += kBonusPerConsecutiveRowErased * consRows;
    }
}
void TetrisGame::OnUpArrowPressed()
{
    //Lets rotate the piece
    
    if(!mCurrFigure || !mGameRunning)
        return;

    mCurrFigure->Rotate();
}

void TetrisGame::OnDownArrowPressed()
{

}

void TetrisGame::OnLeftArrowPressed()
{
    //Lets Move the piece to the left
    if(!mCurrFigure || !mGameRunning)
        return;

    mCurrFigure->MoveLeft(1); 
}

void TetrisGame::OnRightArrowPressed()
{
    //Lets Move the piece to the right
    if(!mCurrFigure || !mGameRunning)
        return;

    mCurrFigure->MoveRight(1); 
}

bool TetrisGame::RandomizeFigureDropLocation()
{
    int trial = kGridColumns;
    int displacement = mWidthSampleSpace(mEngine);
    while(!mCurrFigure->MoveRight(displacement))
    {
        if(trial == 0)
            return false;

        std::cout<<"\nSTDBG::Displacement:"<<displacement;
        //A part of the figure may have crossed the grid boundary.
        //Lets try again
        displacement = mWidthSampleSpace(mEngine);
        trial--;
    }

    return true;
}

void TetrisGame::InitiateGameOver()
{
    std::cout<<"\nGameOver:";
    mGameRunning = false;
    mRenderer->UpdateWindowTitle(" Game Over Score:" + std::to_string(mScore));
}