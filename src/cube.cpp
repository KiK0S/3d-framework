#include "cube.h"

namespace app {

Cube::Cube(): SurfaceObject({
    Point4d(0, 0, 0),
    Point4d(0, 0, kSize_),
    Point4d(0, kSize_, kSize_),
    Point4d(kSize_, kSize_, kSize_),
    Point4d(kSize_, 0, 0),
    Point4d(kSize_, kSize_, 0),
    Point4d(kSize_, 0, kSize_),
    Point4d(0, kSize_, 0)
}, {
    {0, 1}, {0, 7}, {0, 4},
    {1, 2}, {1, 6},
    {2, 3},
    {4, 5}, {4, 6},
    {5, 3},
    {6, 3},
    {7, 2}, {7, 5}
},  {
    {0, 1, 2}, {0, 2, 7}, {0, 1, 4}, {0, 4, 6}, {0, 4, 5}, {0, 5, 6},
    {3, 1, 2}, {3, 1, 6}, {3, 4, 5}, {3, 4, 6}, {3, 5, 7}, {3, 2, 7}
}) {}

}
