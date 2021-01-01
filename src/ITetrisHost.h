#ifndef I_TETRIS_HOST_H
#define I_TETRIS_HOST_H

#include <vector>
struct Point;

class ITetrisHost
{
public:
    virtual bool ValidatePoint(const std::vector<Point>& points) = 0;
};

#endif