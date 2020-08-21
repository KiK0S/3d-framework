#pragma once

#include <cstdlib>
#include <vector>
#include "point.h"

namespace app {

class Matrix {
private:
    static constexpr size_t N = 4;
public:
    Matrix();
    Matrix(const std::array<double, N * N>& data);

    Matrix& operator += (const Matrix& other);
    Matrix& operator -= (const Matrix& other);
    Matrix& operator *= (double k);
    Matrix& operator /= (double k);
    Matrix& operator *= (const Matrix& other);

    Matrix operator -() const ;
    Matrix operator + (const Matrix& other) const ;
    Matrix operator - (const Matrix& other) const ;
    Matrix operator * (double k) const ;
    Matrix operator / (double k) const ;
    Matrix operator * (const Matrix& other) const ;
    Vector4d operator *(const Vector4d& vector) const ;

    static Matrix identity_matrix() ;

    double operator()(size_t row, size_t column) const ;
    double& operator()(size_t row, size_t column);

    Matrix inverse() const ;

private:
    std::array<double, N * N> data_;
};

using Matrix4d = Matrix;

}
