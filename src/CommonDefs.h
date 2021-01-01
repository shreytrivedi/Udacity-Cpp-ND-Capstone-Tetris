#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include <vector>

struct Point
{
    int x;
    int y;
};

using TetrisCanvas = std::vector<std::vector<int>>;

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{250};
constexpr std::size_t kScreenHeight{500};
constexpr std::size_t kGridWidth{32};
constexpr std::size_t kGridHeight{32};
constexpr std::size_t kGridRows{20};
constexpr std::size_t kGridColumns{10};

constexpr std::size_t kMagnificationFactor{25};
constexpr std::size_t kBonusPerConsecutiveRowErased{10};
constexpr std::size_t kScorePerRowErased{10};

#endif