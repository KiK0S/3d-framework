#include "camera.h"
#include "loader.h"
#include "matrix.h"
#include "renderer.h"
#include "surface_object.h"

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace {

constexpr int kWidth = 800;
constexpr int kHeight = 800;

app::Camera camera(kWidth, kHeight);
app::Renderer renderer(kWidth, kHeight);
app::SurfaceObject teapot;
std::vector<uint8_t> frame;
bool loaded = false;
double angle = 0.0;

app::Matrix4d scale_matrix(double scale) {
    return app::Matrix4d{
        scale, 0,     0,     0,
        0,     scale, 0,     0,
        0,     0,     scale, 0,
        0,     0,     0,     1
    };
}

void load_teapot() {
    if (loaded) {
        return;
    }
    teapot = app::Loader::load("/models/teapot.off");
    teapot.apply_transform(scale_matrix(280));
    teapot.apply_transform(app::Matrix4d::construct_moving_matrix(app::Vector4d(-155, 0, 680)));
    loaded = true;
}

void draw_teapot() {
    renderer.clear();
    for (const auto& triangle : teapot.get_triangles()) {
        renderer.draw_triangle(camera, triangle);
    }
    renderer.copy_rgba_to(frame);
}

} // namespace

extern "C" {

int raster_width() {
    return kWidth;
}

int raster_height() {
    return kHeight;
}

const uint8_t* raster_pixels() {
    return frame.data();
}

void raster_init() {
    load_teapot();
    frame.resize(kWidth * kHeight * 4, 255);
    camera.move(app::Vector4d(0, 0, -160));
    camera.rotate(app::Matrix4d::construct_rotation_matrix(0, -0.45));
    camera.rotate(app::Matrix4d::construct_rotation_matrix(2, 0.12));
    draw_teapot();
}

void raster_frame(double delta_seconds) {
    load_teapot();
    const double delta = std::min(delta_seconds, 0.05);
    angle += delta;
    draw_teapot();
}

void raster_move_camera(double x, double y, double z) {
    camera.move(app::Vector4d(x, y, z));
}

void raster_rotate_camera(int axis, double angle) {
    camera.rotate(app::Matrix4d::construct_rotation_matrix(axis, angle));
}

double raster_angle() {
    return angle;
}

}
