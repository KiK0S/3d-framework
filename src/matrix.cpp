#include "classes.h"
#include "matrix.h"
#include <cassert>
#include <vector>
#include <stdexcept>

namespace app {

template<size_t N, size_t M>
Matrix<N, M>::Matrix() {
    data_.assign(N, std::vector<double>(M, 0));
}
template<size_t N, size_t M>
Matrix<N, M>::Matrix(std::vector<std::vector<double>> data): data_(data) {}

template<size_t N, size_t M>
std::vector<double>& Matrix<N, M>::operator[] (size_t n) {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return data_[n];
}

template<size_t N, size_t M>
const std::vector<double>& Matrix<N, M>::operator[] (size_t n) const {
    if (n < 0 || n >= N) {
        throw std::out_of_range("bad index");
    }
    return data_[n];
}

template <size_t N, size_t M>
template <size_t K>
Matrix<N, K> Matrix<N, M>::operator * (Matrix<M, K> other) const {
    Matrix<N, K> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < M; k++) {
                result[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }
    return result;
}

template<size_t N, size_t M>
Vector4d Matrix<N, M>::operator *(Vector4d other) const {
    assert(M == 4);
    Vector4d result(0, 0, 0);
    Matrix<4, 1> v;
    v[0][0] = other.x;
    v[1][0] = other.y;
    v[2][0] = other.z;
    v[3][0] = other.w;
    Matrix<4, 1> pseudo_result = (*this) * v;
    result.x = pseudo_result[0][0];
    result.y = pseudo_result[1][0];
    result.z = pseudo_result[2][0];
    result.w = pseudo_result[3][0];
    return result;
}

template<size_t N, size_t M>
Matrix<N, N> Matrix<N, M>::inverse() const {
    if (N != M) {
        throw std::runtime_error("lel");
    }
    std::vector<std::vector<double>> copy = data_;
    std::vector<std::vector<double>> eye = copy;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            eye[i][j] = 0;
            if (i == j) {
                eye[i][j] = 1;
            }
        }
    }
    for (int j = 0; j < N; j++) {
        for (int i = j; i < N; i++) {
            if (copy[i][j] != 0) {
                std::swap(copy[i], copy[j]);
                std::swap(eye[i], eye[j]);
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
    return Matrix<N, N>(eye);
}

}
