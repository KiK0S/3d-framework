#pragma once

#include "camera.h"
#include "pixel_screen.h"
#include "renderer.h"
#include "surface_object.h"
#include "tetraedr.h"
#include <SFML/Graphics.hpp>
#include <list>

namespace app {

class Renderer;
/*!
    \brief Класс мира в 3д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class World {
public:
    using ObjectPtr = std::unique_ptr<SurfaceObject>;
    using ObjectPtrList = std::list<ObjectPtr>;
    using ObjectPtrListIt = ObjectPtrList::iterator;

    /*!
        \brief Добавление объекта
     */
    ObjectPtrListIt add_object(ObjectPtr&& w);

    /*!
        \brief Добавление объекта
     */
    void erase_object(ObjectPtrListIt it);

    /*!
        \brief итератор на начало списка объектов
     */
    ObjectPtrListIt begin();

    /*!
        \brief итератор на конец списка объектов
     */
    ObjectPtrListIt end();

private:
    std::list<std::unique_ptr<SurfaceObject>> objects_;
};

}
