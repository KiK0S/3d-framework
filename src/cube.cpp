#include "cube.h"

namespace app {

template <typename T>
Cube<T>::Cube() {
    WireObject<T>::points_ = {
        Point4d<T>(0, 0, 0),
        Point4d<T>(0, 0, SIZE),
        Point4d<T>(0, SIZE, SIZE),
        Point4d<T>(SIZE, SIZE, SIZE),
        Point4d<T>(SIZE, 0, 0),
        Point4d<T>(SIZE, SIZE, 0),
        Point4d<T>(SIZE, 0, SIZE),
        Point4d<T>(0, SIZE, 0)
    };
    WireObject<T>::edges_ = {
        {0, 1}, {0, 7}, {0, 4},
        {1, 2}, {1, 6},
        {2, 3},
        {4, 5}, {4, 6},
        {5, 3},
        {6, 3},
        {7, 2}, {7, 5}
    };
}

}
