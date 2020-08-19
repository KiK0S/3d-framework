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

Matrix::Matrix(std::array<double, N * N> data): data_(data) {}
Matrix::Cursor::Cursor(int pos, std::array<double, N * N>* data): pos_(pos), data_(data) {}
Matrix::ConstCursor::ConstCursor(int pos, const std::array<double, N * N>* data): pos_(pos), data_(data) {}

Matrix::Cursor Matrix::operator[] (size_t n) {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return Matrix::Cursor(n * N, &data_);
}

double& Matrix::Cursor::operator[] (size_t n) {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return (*data_)[pos_ + n];
}


Matrix::ConstCursor Matrix::operator[] (size_t n) const {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return Matrix::ConstCursor(n * N, &data_);
}

const double& Matrix::ConstCursor::operator[] (size_t n) const {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return (*data_)[pos_ + n];
}


Matrix Matrix::operator * (Matrix other) const {
    Matrix result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }
    return result;
}

Vector4d Matrix::operator *(Vector4d other) const {
    Vector4d result(0, 0, 0);
    std::array<double, N> tmp;
    for (int i = 0; i < N; i++) {
        tmp[i] = other.x * (*this)[i][0] + other.y * (*this)[i][1] + other.z * (*this)[i][2] + other.w * (*this)[i][3];
    }
    result.x = tmp[0];
    result.y = tmp[1];
    result.z = tmp[2];
    result.w = tmp[3];
    return result;
}

Matrix Matrix::inverse() const {
    Matrix copy = (*this);
    Matrix eye = identity_matrix();

    for (int j = 0; j < N; j++) {
        for (int i = j; i < N; i++) {
            if (copy[i][j] != 0) {
                for (int k = 0; k < N; k++) {
                    std::swap(copy[i][k], copy[j][k]);
                    std::swap(eye[i][k], eye[j][k]);
                }
                break;
            }
        }
        if (copy[j][j] == 0) {
            throw std::runtime_error("lel");
        }
        for (int i = j + 1; i < N; i++) {
            double K = copy[i][j] / copy[j][j];
            for (int k = 0; k < N; k++) {
                copy[i][k] -= copy[j][k] * K;
                eye[i][k] -= eye[j][k] * K;
            }
        }
        double x = copy[j][j];
        for (int i = 0; i < N; i++) {
            copy[j][i] /= x;
            eye[j][i] /= x;
        }
    }
    for (int j = N - 1; j >= 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            double K = copy[i][j] / copy[j][j];
            for (int k = 0; k < N; k++) {
                copy[i][k] -= copy[j][k] * K;
                eye[i][k] -= eye[j][k] * K;
            }
        }
    }
    return eye;
}

Matrix Matrix::identity_matrix() {
    return Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
}

}
