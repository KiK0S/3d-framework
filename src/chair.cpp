#include "chair.h"

namespace app {

Chair::Chair(): SurfaceObject({
    Point4d(0, 0, 0), Point4d(0, kSize_, 0), Point4d(kSize_, kSize_, 0), Point4d(kSize_, 0, 0),
    Point4d(kSize_ / 2, kSize_ / 2, 0),
    Point4d(0, kSize_ / 2, kSize_ / 2), Point4d(kSize_ / 2, kSize_, kSize_ / 2), Point4d(kSize_, kSize_ / 2, kSize_ / 2), Point4d(kSize_ / 2, 0, kSize_ / 2)
}, {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {0, 5}, {1, 5},
    {1, 6}, {2, 6},
    {2, 7}, {3, 7},
    {3, 8}, {0, 8},
    {8, 4}, {7, 4}, {6, 4}, {5, 4}
}, {
    {0, 1, 2},
    {0, 2, 3},
    {5, 0, 1},
    {6, 1, 2},
    {7, 2, 3},
    {8, 0, 3},
    {5, 0, 4},
    {5, 1, 4},
    {6, 1, 4},
    {6, 2, 4},
    {7, 2, 4},
    {7, 3, 4},
    {8, 3, 4},
    {8, 0, 4}
}) {}

}
