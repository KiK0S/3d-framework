#pragma once

#include "classes.h"
#include <cstdlib>
#include <vector>
#include "point.h"

namespace app {

class Matrix {
private:
    struct Cursor;
    struct ConstCursor;
    static constexpr size_t N = 4;
public:
    Matrix();
    Matrix(std::array<double, N * N> data);

    Cursor operator[] (size_t n);
    ConstCursor operator[] (size_t n) const ;

    Matrix operator * (Matrix other) const ;
    Vector4d operator *(Vector4d other) const ;

    static Matrix identity_matrix() ;

    Matrix inverse() const ;

private:
    struct Cursor {
        int pos_;
        std::array<double, N * N>* data_;
        Cursor(int pos, std::array<double, N * N>* data);
        double& operator[] (size_t n);
    };
    struct ConstCursor {
        int pos_;
        const std::array<double, N * N>* data_;
        ConstCursor(int pos, const std::array<double, N * N>* data);
        const double& operator[] (size_t n) const ;
    };
    std::array<double, N * N> data_;
};

using Matrix4d = Matrix;

}
