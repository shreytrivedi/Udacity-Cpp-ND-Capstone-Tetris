#include "Figure.h"

bool BaseFigure::MoveLaterally(int dx)
{
    std::vector<Point> temp = p;
    for(std::size_t i=0;i<temp.size();i++)
    {
        temp[i].x += dx;
    }

    //check if the temp point is valid
    if(mTetrisHost->ValidatePoint(temp))
    {
        p = temp;
        return true;
    }
    else
    {
        return false; //point was not moved
    }
    
}

bool BaseFigure::MoveRight(int dx)
{
    return MoveLaterally(dx);
}

bool BaseFigure::MoveLeft(int dx)
{
    return MoveLaterally(-1*dx);
}

bool BaseFigure::MoveDown(int dy)
{
    std::vector<Point> temp = p;
    for(std::size_t i=0;i<temp.size();i++)
    {
        temp[i].y += dy;
    }

    //check if the temp point is valid
    if(mTetrisHost->ValidatePoint(temp))
    {
        p = temp;   
        return true;
    }
    else
    {
        return false; //point was not moved
    }
}

bool BaseFigure::Rotate()
{
    Point center = p[1]; //center of rotation
    std::vector<Point> temp(4);
    for (std::size_t i=0;i<temp.size();i++)
    {
        int x = p[i].y-center.y;
        int y = p[i].x-center.x;
        temp[i].x = center.x - x;
        temp[i].y = center.y + y;
    }
    
    if(mTetrisHost->ValidatePoint(temp))
    {
        p = temp;
        return true;
    }
    else
    {
        return false; //point was not moved
    }
}