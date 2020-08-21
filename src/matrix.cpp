#include "matrix.h"
#include <cassert>
#include <vector>
#include <stdexcept>

namespace app {

Matrix::Matrix(): data_({
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
}) {}

Matrix::Matrix(const std::array<double, N * N>& data): data_(data) {}

double Matrix::operator()(size_t row, size_t column) const {
    assert(row < N && column < N);
    return data_[N * row + column];
}

double& Matrix::operator()(size_t row, size_t column) {
    assert(row < N && column < N);
    return data_[N * row + column];
}

Matrix& Matrix::operator += (const Matrix& other) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            (*this)(i, j) += other(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator -() const {
    return *this * -1;   
}

Matrix& Matrix::operator -= (const Matrix& other) {
    *this += -other;
    return *this;
}

Matrix& Matrix::operator *= (double k) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            (*this)(i, j) *= k;
        }
    }
    return *this;
}

Matrix& Matrix::operator /= (double k){
    assert(k != 0);
    *this *= 1 / k;
    return *this;
}

Matrix& Matrix::operator *= (const Matrix& other) {
    Matrix copy = (*this);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                (*this)(i, j) += copy(i, k) * other(k, j);
            }
        }
    }
    return *this;
}


Matrix Matrix::operator + (const Matrix& other) const {
    Matrix result = *this;
    result += other;
    return result;
}

Matrix Matrix::operator - (const Matrix& other) const {
    Matrix result = *this;
    result -= other;
    return result;
}

Matrix Matrix::operator * (double k) const {
    Matrix result = *this;
    result *= k;
    return result;
}

Matrix Matrix::operator / (double k) const {
    Matrix result = *this;
    result /= k;
    return result;
}

Matrix Matrix::operator * (const Matrix& other) const {
    Matrix result = *this;
    result *= other;
    return result;
}

Vector4d Matrix::operator *(const Vector4d& vector) const {
    Vector4d result(0, 0, 0);
    std::array<double, N> tmp;
    for (int i = 0; i < N; i++) {
        tmp[i] = vector.x * (*this)(i, 0) + vector.y * (*this)(i, 1) + vector.z * (*this)(i, 2) + vector.w * (*this)(i, 3);
    }
    result.x = tmp[0];
    result.y = tmp[1];
    result.z = tmp[2];
    result.w = tmp[3];
    return result;
}

Matrix Matrix::inverse() const {
    Matrix copy = (*this);
    Matrix result = identity_matrix();

    for (int j = 0; j < N; j++) {
        for (int i = j; i < N; i++) {
            if (copy(i, j) != 0) {
                for (int k = 0; k < N; k++) {
                    std::swap(copy(i, k), copy(j, k));
                    std::swap(result(i, k), result(j, k));
                }
                break;
            }
        }
        double x = copy(j, j);
        // assert(x != 0);
        for (int i = j + 1; i < N; i++) {
            double K = copy(i, j) / x;
            for (int k = 0; k < N; k++) {
                copy(i, k) -= copy(j, k) * K;
                result(i, k) -= result(j, k) * K;
            }
        }
        for (int i = 0; i < N; i++) {
            copy(j, i) /= x;
            result(j, i) /= x;
        }
    }
    for (int j = N - 1; j >= 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            double K = copy(i, j) / copy(j, j);
            for (int k = 0; k < N; k++) {
                copy(i, k) -= copy(j, k) * K;
                result(i, k) -= result(j, k) * K;
            }
        }
    }
    return result;
}

Matrix Matrix::identity_matrix() {
    return Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
}

}
