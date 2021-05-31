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
        \param w unique_ptr на добавляемый SurfaceObject
     */
    void add_object(std::unique_ptr<SurfaceObject>&& w) ;

    /*!
        \brief Сдвиг фокусной позиции камеры на вектор
        \param v вектор сдвига камеры
    */
    void move_camera(const Vector4d& v) ;

    /*!
        \brief Передвинуть все объекты в мире на какой-то вектор
        \param v вектор сдвига
    */
    void move_world(const Vector4d& v) ;

    /*!
        \brief какой-то поворот
        \param angle угол, на который делается поворот
    */
    void roll(double angle) ;

    /*!
        \brief какой-то поворот
        \param angle угол, на который делается поворот
    */
    void pitch(double angle) ;

    /*!
        \brief какой-то поворот
        \param angle угол, на который делается поворот
    */
    void elevation(double angle) ;
    /*!
        \brief какой-то поворот
        \param angle угол, на который делается поворот
    */
    void azimuth(double angle) ;
    /*!
        \brief какой-то поворот
        \param angle угол, на который делается поворот
    */
    void yaw(double angle) ;

    /*!
        \brief поллинг событий
        \param ecent ссылка на событие
        \returns true, если событие произошло и по ссылке записаловь событие, иначе false
    */
    bool poll_event(sf::Event& event);

    /*!
        \brief Проверка, что графическо окно
        \returns true, если окно приложения открыто, иначе false
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
    static int convert_axis_to_int(const EAxes& axe) ;
    void rotate_world(double angle, EAxes fixed_coord) ;
    void draw_object(const std::unique_ptr<SurfaceObject>& object) ;
    void create_keyboard_handlers() ;

    constexpr static size_t kScreenHeight_ = 1000;
    constexpr static size_t kScreenWidth_ = 1000;
    constexpr static size_t kMaxDepth_ = 3000;
    Renderer renderer_;
    World world_;
    Camera camera_;
    sf::RenderWindow window_;
    std::vector<std::pair<sf::Keyboard::Key, std::function<void()>>> keyboard_handlers_;
};

}
