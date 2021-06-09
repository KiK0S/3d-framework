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

Cube::Cube(const Point4d& offset, sf::Color color): SurfaceObject({
    Point4d(offset.x, offset.y, offset.z),
    Point4d(offset.x, offset.y, offset.z + kSize_),
    Point4d(offset.x, offset.y + kSize_, offset.z + kSize_),
    Point4d(offset.x + kSize_, offset.y + kSize_, offset.z + kSize_),
    Point4d(offset.x + kSize_, offset.y, offset.z),
    Point4d(offset.x + kSize_, offset.y + kSize_, offset.z),
    Point4d(offset.x + kSize_, offset.y, offset.z + kSize_),
    Point4d(offset.x, offset.y + kSize_, offset.z)
}, {
    {0, 1}, {0, 7}, {0, 4},
    {1, 2}, {1, 6},
    {2, 3},
    {4, 5}, {4, 6},
    {5, 3},
    {6, 3},
    {7, 2}, {7, 5}
},  {
    {0, 1, 2, color}, {0, 2, 7, color}, {0, 1, 4, color},
    {1, 4, 6, color}, {0, 4, 5, color}, {0, 5, 7, color},
    {3, 1, 2, color}, {3, 1, 6, color}, {3, 4, 5, color},
    {3, 4, 6, color}, {3, 5, 7, color}, {3, 2, 7, color}
}) {}

}
