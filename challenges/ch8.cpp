#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

#include "ray_tracer.h"

using namespace std::chrono;


int main() {

    // Define the spheres
    // left_wall
    Sphere wall = Sphere();
    wall.set_transform(
        translation_matrix(0, 0, -2) * scaling_matrix(1000, 1000, 0.1)
    );
    wall.set_material(
        Material(
            Color(1, 0.9, 0.9), // color
            0.1,                // ambient
            0.5,                // diffuse
            0,                  // specular
            0                   // shininess
        )
    );

    // Palm Sphere
    Sphere palm = Sphere();
    palm.set_transform(translation_matrix(0, 0, 4.5) * scaling_matrix(1, 1, 0.5));
    palm.set_material(
        Material(
            Color(0.1, 1, 0.5), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // Arm Sphere
    Sphere arm = Sphere();
    arm.set_transform(translation_matrix(-3, -1, 5) * rotation_z_matrix(M_PI / 7) * scaling_matrix(3, 1, 0.5));
    arm.set_material(
        Material(
            Color(0.1, 1, 0.5), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // THUMB finger Sphere
    Sphere THUMB = Sphere();
    THUMB.set_transform(translation_matrix(-0.3, 1.1, 5) * scaling_matrix(0.25, 0.57, 0.25));
    THUMB.set_material(
        Material(
            Color(160.0/255.0, 32.0/255.0, 240.0/255.0),   // color
            0.1,                    // ambient
            0.7,                    // diffuse
            0.3,                    // specular
            200.0                   // shininess
        )
    );
    // INDEX finger Sphere
    Sphere INDEX = Sphere();
    INDEX.set_transform(translation_matrix(0.85, 0.42, 5) * scaling_matrix(0.9, 0.21, 0.21));
    INDEX.set_material(
        Material(
            Color(0.8, 0.1, 0.1),   // color
            0.1,                    // ambient
            0.7,                    // diffuse
            0.3,                    // specular
            200.0                   // shininess
        )
    );

    // MIDDLE finger Sphere
    Sphere MIDDLE = Sphere();
    MIDDLE.set_transform(translation_matrix(1, 0, 5) * scaling_matrix(1, 0.25, 0.25));
    MIDDLE.set_material(
        Material(
            Color(0.1, 1, 0.5), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // RING finger Sphere
    Sphere RING = Sphere();
    RING.set_transform(translation_matrix(1, -0.4, 5) * scaling_matrix(1, 0.25, 0.25));
    RING.set_material(
        Material(
            Color(0.9, 0.9, 0), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // PINKY finger Sphere
    Sphere PINKY = Sphere();
    PINKY.set_transform(translation_matrix(0.8, -1, 5) * rotation_z_matrix(-M_PI / 7) * scaling_matrix(0.9, 0.21, 0.21));
    PINKY.set_material(
        Material(
            Color(0, 0.9, 0.9), // color
            0.1,                // ambient
            0.7,                // diffuse
            0.3,                // specular
            200.0               // shininess
        )
    );

    // // BLUE x sphere
    // Sphere x_sphere = Sphere();
    // x_sphere.set_transform(translation_matrix(2, 0, 0) * scaling_matrix(0.5, 0.5, 0.5));
    // x_sphere.set_material(
    //     Material(
    //         Color(0, 0, 1), // color
    //         0.1,                // ambient
    //         0.7,                // diffuse
    //         0.3,                // specular
    //         200.0               // shininess
    //     )
    // );

    // // RED y sphere
    // Sphere y_sphere = Sphere();
    // y_sphere.set_transform(translation_matrix(0, 2, 0) * scaling_matrix(0.5, 0.5, 0.5));
    // y_sphere.set_material(
    //     Material(
    //         Color(1, 0, 0),     // color
    //         0.1,                // ambient
    //         0.7,                // diffuse
    //         0.3,                // specular
    //         200.0               // shininess
    //     )
    // );

    // Add a light source
    PointLight light = PointLight(point(-10, -45, 80), Color(1, 1, 1));

    // Create camera
    unsigned int x = 1000;
    unsigned int y = 1000;
    Camera camera(x, y, M_PI * 1.4 / 3.0);
    camera.transform = view_transform(
        point(2, 2, 8),
        point(-2, 0, 0),
        vector(0, 1, 0)
    );

    // Create world
    World w(
        std::vector<Sphere> {
            wall,
            palm,
            arm,
            // x_sphere,
            // y_sphere,
            THUMB,
            INDEX,
            MIDDLE,
            RING,
            PINKY
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
    std::cout << duration.count() / 1000000.0 << " seconds ";
    std::cout << "(" << duration.count() / (1000000.0 * 60) << " mins)" << std::endl;
    std::cout << duration.count() / (x * y) << " microseconds per pixel." << std::endl;

    return 0;
}
