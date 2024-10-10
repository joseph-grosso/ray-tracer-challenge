#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

#include "ray_tracer.h"

using namespace std::chrono;


// Planes and stripe patterns; chapter 9 with patterns
int main() {
    StripePattern black_stripe = StripePattern(Color(1, 1, 1), Color(0.1, 0.1, 0.1));
    StripePattern maroon = StripePattern(Color(0.9, 0.9, 0.9), Color(0.5, 0, 0), rotation_z_matrix(M_PI / 8) * rotation_y_matrix(-M_PI / 6) * (0.3, 0.3, 0.3) * translation_matrix(0.2, 0, 0) * 0.75);
    StripePattern teal = StripePattern(Color(1, 1, 1), Color(0, 0.5, 0.5), rotation_y_matrix(M_PI / 3) * translation_matrix(0.2, 0, 0));
    StripePattern orange = StripePattern(Color(1, 1, 1), Color(1, 215.0/255.0, 0), scaling_matrix(0.13, 0.13, 0.13F) * rotation_z_matrix(M_PI / 10) * translation_matrix(0.2, 0, 0));

    // Define the objects
    // Floor Plane
    Plane floor = Plane(
        identity_matrix(4),
        Material(
            &black_stripe,
            Color(1, 0.9, 0.9), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                // specular
            0               // shininess
        )
    );

    // Middle Sphere
    Sphere middle = Sphere();
    middle.set_transform(translation_matrix(-0.5, 1, 0.5));
    middle.set_material(
        Material(
            &maroon,
            Color(1, 1, 1), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // Right Sphere
    Sphere right = Sphere();
    right.set_transform(translation_matrix(1.5, 0.5, -0.5) * scaling_matrix(0.5, 0.5, 0.5));
    right.set_material(
        Material(
            &teal,
            Color(1, 1, 1), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // Left Sphere
    Sphere left = Sphere();
    left.set_transform(translation_matrix(-1.5, 0.33, -0.75) * scaling_matrix(0.33, 0.33, 0.33));
    left.set_material(
        Material(
            &orange,
            Color(1, 0.8, 0.1), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // Add a light source
    PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));

    // Create camera
    // unsigned int x = 128;
    // unsigned int y = 72;
    unsigned int x = 1280;
    unsigned int y = 720;
    Camera camera(x, y, M_PI / 3);
    camera.transform = view_transform(
        point(0, 1.5, -5),
        point(0, 1, 0),
        vector(0, 1, 0)
    );

    // Create world
    World w(
        std::vector<Shape *> {
            &floor,
            &middle,
            &left,
            &right
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
