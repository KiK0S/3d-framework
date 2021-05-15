#pragma once

#include "point.h"
#include <cassert>
#include <cstdlib>
#include <vector>

namespace app {
/*!
    \brief Класс для работы с матрицами.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
template
<size_t N, size_t M>
class Matrix {
public:
    void modification_swap(size_t i, size_t j) noexcept {
        assert(i < N && j < N);
        for (int k = 0; k < M; k++) {
            std::swap((*this)(i, k), (*this)(j, k));
        }
    }

    void modification_multiply(size_t i, double k) noexcept {
        assert(i < N);
        for (int j = 0; j < M; j++) {
            (*this)(i, j) *= k;
        }
    }

    void modification_mulsub(size_t i, size_t j, double k) noexcept {
        assert(i < N && j < N);
        for (int t = 0; t < M; t++) {
            (*this)(i, t) -= (*this)(j, t) * k;
        }
    }
private:
    std::array<double, N * M> data_;

public:
    Matrix() {
        for (int i = 0; i < N * M; i++) {
            data_[i] = 0;
        }
    }

    Matrix(const Point4d& p): data_({p.x, p.y, p.z, p.w}) {
        assert(M == 1 && N == 4);
    }

    Matrix(std::array<double, 4>&& data): data_{{std::forward<std::array<double, 4>>(data)}} {}

    Matrix(std::vector<std::vector<double>> initial) {
        for (int i = 0; i < initial.size(); i++) {
            for (int j = 0; j < initial[i].size(); j++) {
                data_[i * M + j] = initial[i][j];
            }
        }
    }
    Matrix(std::initializer_list<double> initial) {
        for (int i = 0; i < N * M; i++) {
            data_[i] = *(initial.begin() + i);
        }
    }

    Matrix(const std::vector<sf::Vector2f>& data) {
        assert(M == 2 && N == data.size());
        for (int i = 0; i < N; i++) {
            (*this)(i, 0) = data[i].x;
            (*this)(i, 1) = data[i].y;
        }
    }

    Matrix(const std::vector<Point4d>& data) {
        assert(M == 4 && N == data.size());
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) = data[i][j];   
            }
        }
    }


    double operator()(size_t row, size_t column) const noexcept {
        assert(row < N && column < M);
        return data_[M * row + column];
    }

    double& operator()(size_t row, size_t column) noexcept {
        assert(row < N && column < M);
        return data_[M * row + column];
    }

    Matrix& operator += (const Matrix& other) noexcept {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this;
    }

    Matrix operator - () const noexcept {
        return *this * -1;
    }

    Matrix& operator -= (const Matrix& other) noexcept {
        *this += -other;
        return *this;
    }

    Matrix& operator *= (double k) noexcept {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) *= k;
            }
        }
        return *this;
    }

    Matrix& operator /= (double k) noexcept {
        assert(k != 0);
        *this *= 1.0 / k;
        return *this;
    }

    Matrix& operator *= (const Matrix& other) noexcept {
        assert(N == M);
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

    bool operator == (const Matrix& other) const noexcept {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator != (const Matrix& other) const noexcept {
        return !(*this == other);
    }

    Matrix operator + (const Matrix& other) const noexcept {
        Matrix result = *this;
        result += other;
        return result;
    }

    Matrix operator - (const Matrix& other) const noexcept {
        Matrix result = *this;
        result -= other;
        return result;
    }

    Matrix operator * (double k) const noexcept {
        Matrix result = *this;
        result *= k;
        return result;
    }

    Matrix operator / (double k) const noexcept {
        Matrix result = *this;
        result /= k;
        return result;
    }

    template <size_t K>
    Matrix<N, K> operator * (const Matrix<M, K>& other) const noexcept {
        Matrix<N, K> result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                for (int k = 0; k < M; k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    Vector4d operator * (const Vector4d& vector) const noexcept {
        assert(M == 4);
        Vector4d result(0, 0, 0);
        std::array<double, M> tmp;
        for (int i = 0; i < N; i++) {
            tmp[i] = vector.x * (*this)(i, 0) + vector.y * (*this)(i, 1) + vector.z * (*this)(i, 2) + vector.w * (*this)(i, 3);
        }
        result.x = tmp[0];
        result.y = tmp[1];
        result.z = tmp[2];
        result.w = tmp[3];
        return result;
    }

    sf::Vector2f operator * (const sf::Vector2f& vector) const noexcept {
        assert(M == 2);
        sf::Vector2f result(0, 0);
        std::array<double, M> tmp;
        for (int i = 0; i < M; i++) {
            tmp[i] = vector.x * (*this)(i, 0) + vector.y * (*this)(i, 1);
        }
        result.x = tmp[0];
        result.y = tmp[1];
        return result;
    }


    static Matrix identity_matrix() noexcept {
        Matrix result;
        for (int i = 0; i < std::min(N, M); i++) {
            result(i, i) = 1;
        }
        return result;
    }


    Point4d row(size_t idx) const noexcept {
        assert(M == 4);
        assert(idx < N);
        return Point4d((*this)(idx, 0) / (*this)(idx, 3), (*this)(idx, 1) / (*this)(idx, 3), (*this)(idx, 2) / (*this)(idx, 3));
    }

    Matrix<M, N> transpose() const noexcept {
        Matrix<M, N> result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    Matrix<N, 1> solve_system(Matrix<N, 1> point) {
        Matrix copy = (*this);
        for (int j = 0; j < M; j++) {
            for (int i = j; i < N; i++) {
                if (copy(i, j) != 0) {
                    copy.modification_swap(i, j);
                    point.modification_swap(i, j);
                    break;
                }
            }
            double x = copy(j, j);
            if (x == 0) {
                return Matrix<N, 1>();
            }
            for (size_t i = j + 1; i < M; i++) {
                double K = copy(i, j) / x;
                copy.modification_mulsub(i, j, K);
                point.modification_mulsub(i, j, K);
            }
            copy.modification_multiply(j, 1.0 / x);
            point.modification_multiply(j, 1.0 / x);
        }
        for (int i = N - 1; i >= 0; i--) {
            for (int j = i + 1; j < M; j++) {
                point(i, 0) -= point(j, 0) * copy(i, j);
            }
        }
        return point;
    }

    Matrix inverse() const {
        assert(N == M);
        Matrix copy = (*this);
        Matrix result = identity_matrix();
        for (int j = 0; j < M; j++) {
            for (int i = j; i < N; i++) {
                if (copy(i, j) != 0) {
                    copy.modification_swap(i, j);
                    result.modification_swap(i, j);
                    break;
                }
            }
            double x = copy(j, j);
            for (int i = j + 1; i < N; i++) {
                double K = copy(i, j) / x;
                copy.modification_mulsub(i, j, K);
                result.modification_mulsub(i, j, K);
            }
            copy.modification_multiply(j, 1.0 / x);
            result.modification_multiply(j, 1.0 / x);
        }
        for (int j = N - 1; j >= 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                double K = copy(i, j) / copy(j, j);
                copy.modification_mulsub(i, j, K);
                result.modification_mulsub(i, j, K);
            }
        }
        return result;
    }

private:
    double det() const {
        assert(N == M);
        Matrix copy = (*this);
        for (int j = 0; j < N; j++) {
            for (int i = j; i < N; i++) {
                if (copy(i, j) != 0) {
                    copy.modification_swap(i, j);
                    break;
                }
            }
            double x = copy(j, j);
            assert(x != 0);
            for (int i = j + 1; i < N; i++) {
                double K = copy(i, j) / x;
                copy.modification_mulsub(i, j, K);
            }
            copy.modification_multiply(j, 1.0 / x);
        }
        for (int j = N - 1; j >= 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                double K = copy(i, j) / copy(j, j);
                copy.modification_mulsub(i, j, K);
            }
        }
        double result = 1;
        for (int i = 0; i < std::min(N, M); i++) {
            result *= copy(i, i);
        }
        return result;
    }
};

using Matrix4d = Matrix<4, 4>;

}