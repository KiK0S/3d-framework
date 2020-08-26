#include "tetraedr.h"

namespace app {

Tetraedr::Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d):
    			   SurfaceObject({a, b, c, d}, {
	                   {0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {0, 3}
				   }),
				   a(a), b(b), c(c), d(d) {}
}
