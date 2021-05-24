#include "cube.h"

namespace app {

/*

    2 - - - - - - 3
     \             \
    | \           | \
       1 - - - - - - 6
    |             |
       |             |
    7              5
     \ |           \ |
      \             \
       0 - - - - - - 4

*/

Cube::Cube(): SurfaceObject({
    Point4d(start.x, start.y, start.z),
    Point4d(start.x, start.y, start.z + kSize_),
    Point4d(start.x, start.y + kSize_, start.z + kSize_),
    Point4d(start.x + kSize_, start.y + kSize_, start.z + kSize_),
    Point4d(start.x + kSize_, start.y, start.z),
    Point4d(start.x + kSize_, start.y + kSize_, start.z),
    Point4d(start.x + kSize_, start.y, start.z + kSize_),
    Point4d(start.x, start.y + kSize_, start.z)
}, {
    {0, 1}, {0, 7}, {0, 4},
    {1, 2}, {1, 6},
    {2, 3},
    {4, 5}, {4, 6},
    {5, 3},
    {6, 3},
    {7, 2}, {7, 5}
},  {
    {0, 1, 2}, {0, 2, 7}, {0, 1, 4}, {1, 4, 6}, {0, 4, 5}, {0, 5, 7},
    {3, 1, 2}, {3, 1, 6}, {3, 4, 5}, {3, 4, 6}, {3, 5, 7}, {3, 2, 7}
}) {}

}
