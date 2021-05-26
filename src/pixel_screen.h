#pragma once

#include <cassert>
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
    PixelScreen(size_t width, size_t height, T default_value = T()):
        height_(height), width_(width), default_value_(default_value),
        data_(height_ * width_, default_value) {}

    T& operator() (size_t row, size_t column) {
        assert(row * width_ + column < data_.size());
        return data_[row * width_ + column];
    }
    const T& operator() (size_t row, size_t column) const {
        assert(row * width_ + column < data_.size());
        return data_[row * width_ + column];
    }

    void clear() {
        std::fill(data_.begin(), data_.end(), default_value_);
    }

private:
    size_t width_;
    size_t height_;
    T default_value_;
    std::vector<T> data_;
};