#include "tetraedr.h"

namespace app {

Tetraedr::Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d):
    WireObject({a, b, c, d}, {
    {0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {0, 3}
}),
a(a), b(b), c(c), d(d) {}

Tetraedr Tetraedr::operator +(const Tetraedr& t) const {
    return Tetraedr(a + t.a, b + t.b, c + t.c, d + t.d);
}

Tetraedr Tetraedr::operator *(float f) const {
    return Tetraedr(a * f, b * f, c * f, d * f);
}

Tetraedr Tetraedr::operator /(float f) const {
    return (*this) * (1 / f);
}


const Tetraedr operator * (float f, Tetraedr t) {
    return t * f;
}

}
