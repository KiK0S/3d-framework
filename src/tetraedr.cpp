#include "tetraedr.h"

namespace app {

Tetraedr::Tetraedr(): SurfaceObject({Point4d(100, 100, 100), Point4d(200, 100, 100), Point4d(100, 200, 200), Point4d(200, 500, 500)},  {
    {0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {0, 3}
}, {{0, 1, 2}, {1, 2, 3}, {0, 2, 3}, {0, 2, 1}}), a(100, 100, 100), b(200, 100, 100), c(100, 200, 200), d(200, 200, 200) {}

Tetraedr::Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d):
    SurfaceObject({a, b, c, d}, {
    {0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {0, 3}
}),
a(a), b(b), c(c), d(d) {}
}
