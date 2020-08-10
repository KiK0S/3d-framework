#include "matrix.h"
#include <cassert>

namespace app {
    template<size_t N, size_t M>
    Matrix<N, M>::Matrix() {
        data_.assign(N, std::vector<double>(M, 0));
    }
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
}