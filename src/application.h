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

    Класс создает окно размера 1000x1000, в котором будут отображаться объекты.
    После вызова метода run() приложение переходит в интерактивный режим
        и реагирует на нажатие на клавиши.
    Для обработки кадра пользоваться update_and_draw_frame()
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

        Стандартные габариты экрана 1000x1000
     */
    Application();

    /*!
        \brief Обновление кадра в приложении.

        Перерисует окно и нанесет на него все объекты, которые сейчас хранятся в мире.
     */
    void update_and_draw_frame();

    /*!
        \brief Сдвиг фокусной позиции камеры
        \param v Вектор сдвига камеры

        После применения фокусная точка камеры сдвигается на вектор v.
    */
    void move_camera(const Vector4d& v) ;

    /*!
        \brief Передвинуть все объекты в мире на какой-то вектор
        \param v Вектор сдвига объектов

        После применения все вершины объектов сдвинуты на вектор v.
    */
    void move_world(const Vector4d& v) ;

    /*!
        \brief Поворот камеры вокруг оси oZ
        \param angle Угол, на который делается поворот

        После применения камера оказывается повернута вокруг оси oZ на угол angle.
    */
    void roll(double angle) ;

    /*!
        \brief Поворот камеры вокруг оси oX
        \param angle Угол, на который делается поворот

        После применения камера оказывается повернута вокруг оси oX на угол angle.
    */
    void pitch(double angle) ;

    /*!
        \brief Поворот камеры вокруг оси oY
        \param angle Угол, на который делается поворот

        После применения камера оказывается повернута вокруг оси oY на угол angle.
    */
    void yaw(double angle) ;

    /*!
        \brief поллинг событий
        \param ecent ссылка на событие
        \returns true, если событие произошло, иначе false

        Если вернуло true, то по ссылке записалось событие
    */
    bool poll_event(sf::Event* event);

    /*!
        \brief Возвращает ми
        \returns Мир World, константная версия
    */
    const World& get_world() const ;

    /*!
        \brief Возвращает мир
        \returns Мир World, константная версия
    */
    World& get_world() ;

    /*!
        \brief Цикл приложения

        Основной метод, который запускает event loop приложения
    */
    void run();

private:

    /*!
        \brief Проверка, что графическо окно открыто
        \returns true, если окно приложения открыто, иначе false
    */
    bool is_open() const ;

    /*!
        \brief Закрыть приложение
    */
    void close() ;

    /*!
        \brief Рисование объекта

        Метод, который с помощью Renderer'a нарисует объект
    */
    void draw_object(const std::unique_ptr<SurfaceObject>& object) ;

    /*!
        \brief Перевод enum-а осей в числовое значение
        \param axe Ось
        \returns число, соответствующее оси

        oX - 0
        oY - 1
        oZ - 2
    */
    static int convert_axis_to_int(const EAxes& axe) ;

    /*!
        \brief Поворот камеры вокруг оси
        \param angle Угол, на который делается поворот
        \param fixed_coord Ось, вокруг которой делается поворот

        Используется для реализации roll, yaw, pitch
    */
    void rotate_camera(double angle, EAxes fixed_coord) ;

    /*!
        \brief Создание хэндлеров

        Создает список хэндлеров, которые будут реагировать на нажатия на клавиши
    */
    void create_keyboard_handlers() ;

    constexpr static size_t kScreenHeight_ = 1000;
    constexpr static size_t kScreenWidth_ = 1000;
    Renderer renderer_;
    World world_;
    Camera camera_;
    sf::RenderWindow window_;
    std::vector<std::pair<sf::Keyboard::Key, std::function<void()>>> keyboard_handlers_;
};

}
