#pragma once

#include "point.h"
#include <cassert>
#include <cmath>
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
private:
    template
    <size_t N_, size_t M_>
    friend class Matrix;
    std::array<double, N * M> data_;

public:
    /*!
        \brief Конструктор, делающий нулевую матрицу
    */
    Matrix() {
        for (int i = 0; i < N * M; i++) {
            data_[i] = 0;
        }
    }

    /*!
        \brief Конструктор, создающий матрицу по четырехмерной точке
    */
    Matrix(const Point4d& p): data_{{p.x, p.y, p.z, p.w}} {
        static_assert(M == 1 && N == 4);
    }

    /*!
        \brief Конструктор, создающий матрицу по двумерному вектору
    */
    Matrix(const sf::Vector2f& v): data_{{v.x, v.y}} {
        static_assert(M == 1 && N == 2);
    }

    /*!
        \brief Конструктор, создающий матрицу из массива со всеми ее элементами
    */
    Matrix(const std::array<double, N * M>& data): data_{data_} {}

    /*!
        \brief Конструктор, создающий матрицу из списка ее элементов
    */
    Matrix(std::initializer_list<double> initial) {
        for (int i = 0; i < N * M; i++) {
            data_[i] = *(initial.begin() + i);
        }
    }

    /*!
        \brief Конструктор, создающий матрицу по массиву двумерных векторов
    */
    Matrix(const std::vector<sf::Vector2f>& data) {
        static_assert(M == 2);
        assert(N == data.size());
        for (int i = 0; i < N; i++) {
            (*this)(i, 0) = data[i].x;
            (*this)(i, 1) = data[i].y;
        }
    }

    /*!
        \brief Конструктор, создающий матрицу по массиву четырехмерных точек
    */
    Matrix(const std::vector<Point4d>& data) {
        static_assert(M == 4);
        assert(N == data.size());
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) = data[i](j);
            }
        }
    }

    /*!
        \brief Оператор доступа к элементу матрицы
        \param row ряд
        \param column колонка
        \returns A[row][column]
    */
    double operator()(size_t row, size_t column) const {
        assert(row < N && column < M);
        return data_[M * row + column];
    }

    /*!
        \brief Оператор доступа к элементу матрицы
        \param row ряд
        \param column колонка
        \returns A[row][column]
    */
    double& operator()(size_t row, size_t column) {
        assert(row < N && column < M);
        return data_[M * row + column];
    }

    /*!
        \brief Оператор прибавления  матрицы по правилу A[x][y] += B[x][y]
    */
    Matrix& operator += (const Matrix& other) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this;
    }

    /*!
        \brief Оператор получения матрицы с обратным знаком: A[x][y] -> -A[x][y]
    */
    Matrix operator - () const {
        return *this * -1;
    }

    /*!
        \brief Оператор вычитания матрицы по правилу A[x][y] -= B[x][y]
    */
    Matrix& operator -= (const Matrix& other) {
        *this += -other;
        return *this;
    }

    /*!
        \brief Оператор домножения матрицы на число по правилу A[x][y] *= k
    */
    Matrix& operator *= (double k) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)(i, j) *= k;
            }
        }
        return *this;
    }

    /*!
        \brief Оператор деления матрицы на число по правилу A[x][y] /= k
    */
    Matrix& operator /= (double k) {
        assert(k != 0);
        *this *= 1.0 / k;
        return *this;
    }

    /*!
        \brief Оператор домножения матрицы на число по правилу A[x][y] *= k
    */
    Matrix operator * (double k) const {
        Matrix result = *this;
        result *= k;
        return result;
    }

    /*!
        \brief Оператор деления матрицы на число по правилу A[x][y] /= k
    */
    Matrix operator / (double k) const {
        Matrix result = *this;
        result /= k;
        return result;
    }

    /*!
        \brief Оператор домножения квадратной матрицы на матрицу
    */
    Matrix& operator *= (const Matrix& other) {
        static_assert(N == M);
        Matrix copy = (*this);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                (*this)(i, j) = 0;
                for (int k = 0; k < N; k++) {
                    (*this)(i, j) += copy(i, k) * other(k, j);
                }
            }
        }
        return *this;
    }

    /*!
        \brief Оператор сравнения матриц по правилу A[x][y] == B[x][y]
    */
    template <size_t N_, size_t M_>
    friend bool operator == (const Matrix<N_, M_>& first,
                             const Matrix<N_, M_>& second);
    /*!
        \brief Оператор проверки матриц на неравенство по правилу A[x][y] == B[x][y]
    */
    template <size_t N_, size_t M_>
    friend bool operator != (const Matrix<N_, M_>& first,
                             const Matrix<N_, M_>& second);

    /*!
        \brief Оператор сложения матриц по правилу A[x][y] + B[x][y]
    */
    template <size_t N_, size_t M_>
    friend Matrix<N_, M_> operator + (const Matrix<N_, M_>& first,
                                      const Matrix<N_, M_>& second);
    /*!
        \brief Оператор вычитания матриц по правилу A[x][y] - B[x][y]
    */
    template <size_t N_, size_t M_>
    friend Matrix<N_, M_> operator - (const Matrix<N_, M_>& first,
                                      const Matrix<N_, M_>& second) ;
    /*!
        \brief Оператор перемножения матриц
    */
    template <size_t N_, size_t M_, size_t K>
    friend Matrix<N_, K> operator * (const Matrix<N_, M_>& first,
                                     const Matrix<M_, K>& second);

    /*!
        \brief Получение единичной матрицы: A[x][x] = 1, A[x][y] = 0
    */
    static Matrix identity_matrix() {
        Matrix result;
        for (int i = 0; i < std::min(N, M); i++) {
            result(i, i) = 1;
        }
        return result;
    }

    /*!
        \brief Получение матрицы для сдвига на вектор в четырехмерном пространстве
    */
    static Matrix construct_moving_matrix(const Vector4d& moving_vector) {
        static_assert(M == 4 && N == 4);
        assert(moving_vector.w != 0);
        Matrix move = identity_matrix();
        move(0, 3) = moving_vector.x / moving_vector.w;
        move(1, 3) = moving_vector.y / moving_vector.w;
        move(2, 3) = moving_vector.z / moving_vector.w;
        return move;
    }

    /*!
        \brief Получение матрицы для поворота в четырехмерном пространстве
    */
    static Matrix construct_rotation_matrix(int fixed_coordinate, double angle) {
        static_assert(M == 4 && N == 4);
        assert(fixed_coordinate >= 0 && fixed_coordinate <= 2);
        // oX, oY, oZ <-> 0, 1, 2
        Matrix rotation = identity_matrix();
        rotation((fixed_coordinate + 1) % 3, (fixed_coordinate + 1) % 3) = std::cos(angle);
        rotation((fixed_coordinate + 2) % 3, (fixed_coordinate + 2) % 3) = std::cos(angle);
        rotation((fixed_coordinate + 1) % 3, (fixed_coordinate + 2) % 3) = -std::sin(angle);
        rotation((fixed_coordinate + 2) % 3, (fixed_coordinate + 1) % 3) = std::sin(angle);
        return rotation;
    }

private:
    Matrix& swap_rows(size_t i, size_t j) {
        assert(i < N && j < N);
        for (int k = 0; k < M; k++) {
            std::swap((*this)(i, k), (*this)(j, k));
        }
        return *this;
    }

    Matrix& multiply_row(size_t i, double k) {
        assert(i < N);
        for (int j = 0; j < M; j++) {
            (*this)(i, j) *= k;
        }
        return *this;
    }

    Matrix& multiply_then_substract_row(size_t i, size_t j, double k) {
        assert(i < N && j < N);
        for (int t = 0; t < M; t++) {
            (*this)(i, t) -= (*this)(j, t) * k;
        }
        return *this;
    }

    int find_optimal_row(size_t column) const {
        int optimal = -1;
        double max_abs_value = 0;
        for (size_t row = column; row < N; row++) {
            if (std::abs((*this)(row, column)) != 0) {
                max_abs_value = std::abs((*this)(row, column));;
                optimal = row;
                break;
            }
        }
        return optimal;
    }

    template <size_t _M>
    void clear_column(int column, Matrix<N, _M> *paired, double k) {
        for (int row = column + 1; row < M; row++) {
            double coefficient = (*this)(row, column) / k;
            multiply_then_substract_row(row, column, coefficient);
            paired->multiply_then_substract_row(row, column, coefficient);
        }
    }

    template <size_t _M>
    void convert_to_upper_triangular(Matrix<N, _M>* paired) {
        for (int j = 0; j < std::min(N, M); j++) {
            int id = this->find_optimal_row(j);
            if (id == -1) {
                return;
            }
            this->swap_rows(id, j);
            paired->swap_rows(id, j);
            double x = (*this)(j, j);
            if (x == 0) {
                return ;
            }
            this->clear_column(j, paired, x);
        }
    }

public:
    /*!
        \brief Получение транспонированной матрицы
    */
    Matrix<M, N> transpose() const {
        Matrix<M, N> result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    /*!
        \brief Решение системы уравнений Ax = point
    */
    Matrix<N, 1> solve_system(Matrix<N, 1> point) const {
        Matrix copy = (*this);
        copy.convert_to_upper_triangular(&point);
        for (int i = N - 1; i >= 0; i--) {
            for (int j = i + 1; j < M; j++) {
                point(i, 0) -= point(j, 0) * copy(i, j);
            }
            assert(copy(i, i) != 0);
            point(i, 0) /= copy(i, i);
        }
        return point;
    }

    /*!
        \brief Получение обратной матрицы
    */
    Matrix inverse() const {
        static_assert(N == M);
        Matrix copy = (*this);
        Matrix result = identity_matrix();
        copy.convert_to_upper_triangular(&result);
        for (int j = N - 1; j >= 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                double K = copy(i, j) / copy(j, j);
                copy.multiply_then_substract_row(i, j, K);
                result.multiply_then_substract_row(i, j, K);
            }
        }
        return result;
    }
};

using Matrix4d = Matrix<4, 4>;
using Matrix2d = Matrix<2, 2>;

template<size_t N, size_t M>
bool operator == (const Matrix<N, M>& first,
                  const Matrix<N, M>& second) {
    static constexpr double EPS = 1e-6;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (std::abs(first(i, j) - second(i, j)) > EPS) {
                return false;
            }
        }
    }
    return true;
}

template<size_t N, size_t M>
bool operator != (const Matrix<N, M>& first,
                  const Matrix<N, M>& second) {
    return !(first == second);
}


template<size_t N, size_t M>
Matrix<N, M> operator + (const Matrix<N, M>& first,
                         const Matrix<N, M>& second) {
    Matrix result = first;
    result += second;
    return result;
}

template<size_t N, size_t M>
Matrix<N, M> operator - (const Matrix<N, M>& first,
                         const Matrix<N, M>& second) {
    Matrix result = first;
    result -= second;
    return result;
}

template <size_t N, size_t M, size_t K>
Matrix<N, K> operator * (const Matrix<N, M>& first,
                         const Matrix<M, K>& second) {
    Matrix<N, K> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < M; k++) {
                result(i, j) += first(i, k) * second(k, j);
            }
        }
    }
    return result;
}

template<size_t N, size_t M>
Vector4d operator * (const Matrix<N, M>& matrix,
                     const Vector4d& vector) {
    static_assert(M == 4);
    Vector4d result(0, 0, 0);
    std::array<double, M> tmp;
    for (int i = 0; i < N; i++) {
        tmp[i] = vector.x * matrix(i, 0) + vector.y * matrix(i, 1) +
                 vector.z * matrix(i, 2) + vector.w * matrix(i, 3);
    }
    result.x = tmp[0];
    result.y = tmp[1];
    result.z = tmp[2];
    result.w = tmp[3];
    return result;
}

template <size_t N, size_t M>
sf::Vector2f operator * (const Matrix<N, M> &matrix, const sf::Vector2f& vector) {
    static_assert(M == 2);
    sf::Vector2f result(0, 0);
    std::array<double, M> tmp;
    for (int i = 0; i < M; i++) {
        tmp[i] = vector.x * matrix(i, 0) + vector.y * matrix(i, 1);
    }
    result.x = tmp[0];
    result.y = tmp[1];
    return result;
}


}