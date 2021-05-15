#pragma once

#include "renderer.h"
#include "world.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

namespace app {

/*!
    \brief Класс инстантса графического приложения.
    \author KiK0S
    \version 1.0
    \date May 14 2021
 */
class Application {
public:
    Application();
    ~Application();

/*!
    \brief Обновление кадра в приложении.
 */
    void update();
    
/*!
    \brief Добавление объекта на сцену.
 */ 
    void add_object(SurfaceObject* w) const ;

/*!
    \brief Сдвиг камеры на вектор
*/ 
    void move_camera(Vector4d v) const ;

/*!
    \brief Передвинуть все элементы на какой-то вектор
*/
    void move_world(Vector4d v) const ;
  
/*!
    \brief какой-то поворот
*/  
    void pitch(double angle) const ;

/*!
    \brief какой-то поворот
*/  
    void roll(double angle) const ;

/*!
    \brief какой-то поворот
*/  
    void elevation(double angle) const ;
/*!
    \brief какой-то поворот
*/  
    void azimuth(double angle) const ;
/*!
    \brief какой-то поворот
*/  
    void yaw(double angle) const ;

/*!
    \brief поллинг событий
*/
    bool poll_event(sf::Event& event);

/*!
    \brief Проверка, что графическо окно
*/
    bool is_open() const ;

/*!
    \brief Закрыть приложение
*/
    void close(); ;
private:
    Renderer * const renderer_;
    World * const world_;
};

}
