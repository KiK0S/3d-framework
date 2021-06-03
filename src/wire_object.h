#pragma once

#include "point.h"
#include "matrix.h"
#include <vector>
#include <utility>

namespace app {
/*!
    \brief Класс каркаса объекта в 3д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class WireObject {
public:

    /*!
        \brief Конструктор каркаса объекта
     */
    WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges);
    virtual ~WireObject();

    /*!
        \brief итератор на начало списка вершин
     */
    typename std::vector<Point4d>::iterator begin() {
        return points_.begin();
    }

    /*!
        \brief итератор на конец списка вершин
     */
    typename std::vector<Point4d>::iterator end() {
        return points_.end();
    }

    /*!
        \brief Применение преобразвания к объекту
     */
    void apply_transform(const Matrix4d& transform);

    /*!
        \brief Массив всех ребер объекта
     */
    std::vector<std::pair<Point4d, Point4d>> get_edges() const;

protected:
    std::vector<Point4d> points_;
    std::vector<std::pair<int, int>> edges_;
};

}
