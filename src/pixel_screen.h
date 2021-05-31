#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace app {

/*!
    \brief Класс контейнера данных для пиксельного экрана.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
template <typename T>
class PixelScreen {
public:
    /*!
        \brief Создание контейнера для данных на экране
    */
    PixelScreen(size_t width, size_t height, T default_value = T()):
        height_(height), width_(width), default_value_(default_value),
        data_(height_ * width_, default_value) {}

    /*!
        \brief Получение данных в заданном пикселе
    */
    T& operator() (size_t row, size_t column) {
        assert(row * width_ + column < data_.size());
        return data_[row * width_ + column];
    }

    /*!
        \brief Получение данных в заданном пикселе
    */
    const T& operator() (size_t row, size_t column) const {
        assert(row * width_ + column < data_.size());
        return data_[row * width_ + column];
    }

    /*!
        \brief Очистка экрана
    */
    void clear() {
        std::fill(data_.begin(), data_.end(), default_value_);
    }

    /*!
        \brief Получение ширины экрана
    */
    size_t get_width() const {
        return width_;
    }

    /*!
        \brief Получение высоты экрана
    */
    size_t get_height() const {
        return height_;
    }

private:
    size_t width_;
    size_t height_;
    T default_value_;
    std::vector<T> data_;
};
}