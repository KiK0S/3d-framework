#include "tetraedr.h"

namespace app {
    template <typename T>
    Tetraedr<T>::Tetraedr(Point4d<T> a, Point4d<T>b, Point4d<T> c, Point4d<T> d): a(a), b(b), c(c), d(d) {
        WireObject<T>::points_ = {a, b, c, d};
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                WireObject<T>::edges_.emplace_back(i, j);
            }
        }
    }

    template <typename T>
    Tetraedr<T> Tetraedr<T>::operator +(const Tetraedr& t) const {
    	return Tetraedr(a + t.a, b + t.b, c + t.c, d + t.d);
    }

    template <typename T>
    Tetraedr<T> Tetraedr<T>::operator *(float f) const {
        return Tetraedr(a * f, b * f, c * f, d * f);
    }

    template <typename T>
    Tetraedr<T> Tetraedr<T>::operator /(float f) const {
        return (*this) * (1 / f);
    }

    template <typename T>
    Tetraedr<T>::~Tetraedr(){}

    template<typename T>
    const Tetraedr<T> operator * (float f, Tetraedr<T> t) {
        return t * f;
    }
}