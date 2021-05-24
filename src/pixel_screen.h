#pragma once

#include <cstddef>
#include <vector>

/*!
    \brief Класс пиксельного экрана.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
template <typename T>
class PixelScreen {
public:
    PixelScreen(size_t width, size_t height): height_(height), width_(width), data_(height_ * width_) {}

    T& operator() (size_t row, size_t column) {
        return data_[row * width_ + column];
    }
    const T& operator() (size_t row, size_t column) const {
        return data_[row * width_ + column];
    }

private:
    size_t width_;
    size_t height_;
    std::vector<T> data_;
};