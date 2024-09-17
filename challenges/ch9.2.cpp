#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

#include "ray_tracer.h"

using namespace std::chrono;


// Hexagonal room 
int main() {

    // Walls
    // floor
    Plane floor = Plane(
        identity_matrix(4),
        Material(
            Color(1, 0.9, 0.9), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // left_wall
    Plane left_wall = Plane(
        translation_matrix(-5.0, 0, 0) * rotation_z_matrix(M_PI / 2),
        Material(
            Color(1, 0, 0), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // left_mid_wall
    Plane left_mid_wall = Plane(
        translation_matrix(0, 0, 5.77) * rotation_y_matrix(- M_PI / 6)* rotation_x_matrix(M_PI / 2),
        Material(
            Color(0.66, 0, 0.34), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // right_mid_wall
    Plane right_mid_wall = Plane(
        translation_matrix(0, 0, 5.77) * rotation_y_matrix(M_PI / 6)* rotation_x_matrix(M_PI / 2),
        Material(
            Color(0.34, 0, 0.66), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // right_wall
    Plane right_wall = Plane(
        translation_matrix(5.0, 0, 0) * rotation_z_matrix(M_PI / 2),
        Material(
            Color(0, 0, 1), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // roof
    Plane roof = Plane(
        translation_matrix(0, 5, 0),
        Material(
            Color(1, 0.9, 0.9), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // First (Large, Green) Sphere
    Sphere middle = Sphere(
        scaling_matrix(2, 1.5, 2),
        Material(
            Color(0.1, 1, 0.5), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    middle.set_material(
        Material(
            Color(0.1, 1, 0.5), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // Add a light source
    PointLight light = PointLight(point(-4, 4, -4), Color(1, 1, 1));

    // Create camera
    unsigned int x = 100;
    unsigned int y = 70;
    Camera camera(x, y, M_PI / 2);
    camera.transform = view_transform(
        point(0, 3, -5),
        point(0, 1.3, 0),
        vector(0, 1, 0)
    );

    // Create world
    World w(
        std::vector<Shape *> {
            &floor,
            &left_wall,
            &left_mid_wall,
            &right_mid_wall,
            &right_wall,
            &roof,
            &middle
        },
        light
    );

    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "New image generation starting!" << std::endl;

    // Track how long the actual loops took
    auto start = high_resolution_clock::now();

    // Render the result
    Canvas image = camera.render(w);

    auto stop = high_resolution_clock::now();

    std::string filename = "values.ppm";
    image.write_to_ppm(filename);

    std::cout << "Charted at " << filename << std::endl;

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << " microseconds." << std::endl;
    std::cout << duration.count() / 1000000.0 << " seconds." << std::endl;
    std::cout << duration.count() / (x * y) << " microseconds per pixel." << std::endl;

    return 0;
}
