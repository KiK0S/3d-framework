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
    PixelScreen(size_t size): size_(size), data_(size * size) {}

    T& operator() (size_t row, size_t column) {
        return data_[row * size_ + column];
    }
    const T& operator() (size_t row, size_t column) const {
        return data_[row * size_ + column];
    }

private:
    size_t size_;
    std::vector<T> data_;
};