#include "../src/point.h"
#include "../src/matrix.h"
#include "../src/triangle.h"
#include "../src/camera.h"
#include "../src/screen.h"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <cxxtest/TestSuite.h>

class UnitTest : public CxxTest::TestSuite
{
public:
    static constexpr double PI{3.141592653589793238462643};
    static constexpr double EPS{0.000001};

    void testPoint(void) {
    	app::Point4d a(0, 0, 0);
    	app::Point4d b(1, 2, 3);
        TS_ASSERT((a + b).x == 1);
        TS_ASSERT((a + b) == (b + a));
        TS_ASSERT(app::scalar((a + b), b) == b.length() * b.length());
    }

    void testMatrix(void) {
    	app::Matrix4d matrix{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1};
    	app::Matrix4d eye = app::Matrix4d::identity_matrix();
    	TS_ASSERT_EQUALS(matrix * eye, matrix);
    	TS_ASSERT_EQUALS(eye * matrix, matrix);
        TS_ASSERT_EQUALS((matrix * matrix), app::Matrix4d({1, 0, 0, 2, 0, 1, 0, 2, 0, 0, 1, 2, 0, 0, 0, 1}));
    	TS_ASSERT_EQUALS((matrix * matrix.inverse()), eye);
        app::Matrix4d move = app::Matrix4d::construct_moving_matrix({1, 2, 1});
        app::Point4d p(1, 2, 3);
        TS_ASSERT_EQUALS(move * p, app::Point4d(2, 4, 4));
        TS_ASSERT_EQUALS(move, app::Matrix4d({1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 1, 0, 0, 0, 1}));

        app::Matrix4d simple_rotate = app::Matrix4d::construct_rotation_matrix(2, PI / 2);
        app::Matrix4d simple_rotate_true = app::Matrix4d({0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        for (int i = 0; i < 16; i++) {
            TS_ASSERT_DELTA(simple_rotate(i / 4, i % 4), simple_rotate_true(i / 4, i % 4), EPS);
        }
        app::Matrix4d rotate = app::Matrix4d::construct_rotation_matrix(2, PI / 4);
        app::Point4d rotated = (rotate * app::Point4d(1, 0, 10));
        app::Point4d rotated_true = app::Point4d(std::sqrt(2) / 2, std::sqrt(2) / 2, 10);
        TS_ASSERT_DELTA(rotated.x, rotated_true.x, EPS);
        TS_ASSERT_DELTA(rotated.y, rotated_true.y, EPS);
        TS_ASSERT_DELTA(rotated.z, rotated_true.z, EPS);
        rotate *= app::Matrix4d::construct_rotation_matrix(2, -PI / 4);
        rotated = (rotate * app::Point4d(1, 0, 10));
        rotated_true = app::Point4d(1, 0, 10);
        TS_ASSERT_DELTA(rotated.x, rotated_true.x, EPS);
        TS_ASSERT_DELTA(rotated.y, rotated_true.y, EPS);
        TS_ASSERT_DELTA(rotated.z, rotated_true.z, EPS);

        app::Matrix<2, 2> system({1, 1, 0, 1});
        app::Matrix<2, 1> solution = system.solve_system({2, 1});
        app::Matrix<2, 1> solution_correct({1, 1});
        TS_ASSERT_DELTA(solution(0, 0), solution_correct(0, 0), EPS);
        TS_ASSERT_DELTA(solution(1, 0), solution_correct(1, 0), EPS);
    }

    void testTriangle() {
    	app::Triangle2d triangle({0, 0}, {1, 0}, {0, -1});
    	TS_ASSERT(triangle.inner_point({0.5, -0.5}));
    	TS_ASSERT(triangle.inner_point({0.5, -0.4}));
    	TS_ASSERT(!triangle.inner_point({1.05, -0.02}));
    	TS_ASSERT_EQUALS(triangle.get_order(), (std::array<int, 3>({2, 1, 0})));
    }

    void testCamera() {
        app::Camera camera(1000, 1000);
        app::Point4d near_plane_point(100, 100, 400); // assuming camera.kLeftPoint_.z = 400
        app::Point4d far_plane_point(100, 100, 5000); // assuming camera.kRightPoint_.z = 5000
        app::Point4d super_far_point(100, 100, 5100); // assuming camera.kRightPoint_.z = 5000
        app::Point4d middle_point(50, -100, 1000); // assuming last two assumings
        TS_ASSERT_EQUALS(near_plane_point, camera.transform_to_cameras_coordinates(near_plane_point));
        TS_ASSERT_EQUALS(far_plane_point, camera.transform_to_cameras_coordinates(far_plane_point));
        TS_ASSERT_EQUALS(middle_point, camera.transform_to_cameras_coordinates(middle_point));
        TS_ASSERT_DELTA(camera.get_z_value(near_plane_point), -1.0, EPS);
        TS_ASSERT_DELTA(camera.get_z_value(far_plane_point), 1.0, EPS);
        TS_ASSERT(camera.get_z_value(super_far_point) > 1);
        double z_middle = camera.get_z_value(middle_point);
        TS_ASSERT(z_middle >= -1 && z_middle <= 1);
        TS_ASSERT_EQUALS(sf::Vector2f(750 - 0.5, 750 - 0.5), camera.project_on_screen(near_plane_point));

        camera.move(app::Point4d(-100, -100, 0));
        TS_ASSERT_EQUALS(sf::Vector2f(1000 - 0.5, 1000 - 0.5).x, camera.project_on_screen(camera.transform_to_cameras_coordinates(near_plane_point)).x);
        TS_ASSERT_EQUALS(sf::Vector2f(1000 - 0.5, 1000 - 0.5).y,camera.project_on_screen(camera.transform_to_cameras_coordinates(near_plane_point)).y);
        camera.move(app::Point4d(0, 0, -100));
        TS_ASSERT_EQUALS(app::Point4d(200, 200, 500).x, camera.transform_to_cameras_coordinates(near_plane_point).x);
        TS_ASSERT_EQUALS(app::Point4d(200, 200, 500).y, camera.transform_to_cameras_coordinates(near_plane_point).y);
        TS_ASSERT_EQUALS(app::Point4d(200, 200, 500).z, camera.transform_to_cameras_coordinates(near_plane_point).z);
        TS_ASSERT_EQUALS(sf::Vector2f(750 - 0.5, 750 - 0.5).x, camera.project_on_screen(camera.transform_to_cameras_coordinates(near_plane_point)).x);
        TS_ASSERT_EQUALS(sf::Vector2f(750 - 0.5, 750 - 0.5).y, camera.project_on_screen(camera.transform_to_cameras_coordinates(near_plane_point)).y);

        camera.move(app::Point4d(100, 100, 100)); // again in (0; 0; 0)
        camera.rotate(app::Matrix4d::construct_rotation_matrix(2, PI / 4));
        TS_ASSERT_DELTA(camera.get_z_value(near_plane_point), -1.0, EPS);
        TS_ASSERT_DELTA(camera.get_z_value(near_plane_point), -1.0, EPS);
    }

    void testScreen() {
        app::Screen screen(1000, 1000);
        screen.set_pixel(1, 1, 0.5, sf::Color::Black);
        screen.set_pixel(1, 2, 0.5, sf::Color::Red);
        screen.set_pixel(1, 1, -0.4, sf::Color::Red);
        std::vector<sf::Vertex> pixels = screen.get_pixels_to_draw();
        TS_ASSERT_EQUALS(pixels.size(), 2);
        TS_ASSERT_EQUALS(pixels[0].color, sf::Color::Red);
        TS_ASSERT_EQUALS(pixels[1].color, sf::Color::Red);
    }
};