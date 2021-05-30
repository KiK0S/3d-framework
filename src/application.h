#pragma once

#include "renderer.h"
#include "world.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

namespace app {

/*!
    \brief Класс инстанса графического приложения.
    \author KiK0S
    \version 1.0
    \date May 14 2021
 */
class Application {
private:
    enum class EAxes {
        AXE_X = 0,
        AXE_Y = 1,
        AXE_Z = 2
    };

public:
    /*!
        \brief Конструктор приложения.
     */
    Application();

    /*!
        \brief Обновление кадра в приложении.
     */
    void update_and_draw_frame();

    /*!
        \brief Добавление объекта на сцену.
     */
    void add_object(std::unique_ptr<SurfaceObject>&& w) ;

    /*!
        \brief Сдвиг позиции камеры на вектор
    */
    void move_camera(const Vector4d& v) ;

    /*!
        \brief Передвинуть все объекты в мире на какой-то вектор
    */
    void move_world(const Vector4d& v) ;

    /*!
        \brief какой-то поворот
    */
    void roll(double angle) ;

    /*!
        \brief какой-то поворот
    */
    void pitch(double angle) ;

    /*!
        \brief какой-то поворот
    */
    void elevation(double angle) ;
    /*!
        \brief какой-то поворот
    */
    void azimuth(double angle) ;
    /*!
        \brief какой-то поворот
    */
    void yaw(double angle) ;

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
    void close() ;

    /*!
        \brief Цикл приложения
    */
    void run();

private:
    void rotate_world(double angle, EAxes fixed_coord) ;
    static int convert_axis_to_int(const EAxes& axe) ;
    static Matrix4d construct_rotation_matrix(int fixed_coordinate, double angle) ;
    void draw_object(const std::unique_ptr<SurfaceObject>& object) ;

    Renderer renderer_;
    World world_;
    Camera camera_;
    sf::RenderWindow window_;
    constexpr static size_t kScreenHeight_ = 1000;
    constexpr static size_t kScreenWidth_ = 1000;
};

}
