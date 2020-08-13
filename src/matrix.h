#pragma once

#include "classes.h"
#include <cstdlib>
#include <vector>
#include "point.h"

namespace app {

template <size_t N, size_t M>
class Matrix {
public:
    Matrix();
    Matrix(std::vector<std::vector<double>>);

    std::vector<double>& operator[] (size_t n);
    const std::vector<double>& operator[] (size_t n) const ;

    template <size_t K>
    Matrix<N, K> operator * (Matrix<M, K> other) const ;
    Vector4d operator *(Vector4d other) const ;

    Matrix<N, N> inverse() const ;

private:
    std::vector<std::vector<double>> data_;
};

using Matrix3d = Matrix<3, 3>;
using Matrix4d = Matrix<4, 4>;

}
