#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

#include "ray_tracer.h"

using namespace std::chrono;


int main() {
    // Create camera
    Tuple camera_origin = point(0, 0, 6);

    // Define the limits of the "screen"
    Tuple bot_left = point(-5, -5, -5);
    Tuple top_right = point(5, 5, -5);

    // Define how we're going to move the ray along the canvas
    Tuple right_movement = vector(10, 0, 0);
    Tuple up_movement = vector(0, 10, 0);

    // Define the sphere and set its transform
    Sphere s = Sphere();
    Matrix t = scaling_matrix(2, 0.7, 1);
    Matrix shear = shearing_matrix(0, 0, 0.5, 0, 0, 0);
    s.set_transform(t * shear);

    // Assign a material to your sphere
    Material m = Material(
        Color(0.3, 1, 0.3), // color
        0.1,            // ambient
        0.5,            // diffuse
        0.9,            // specular
        200.0           // shininess
    );
    s.set_material(m);
    Material get_material_val = s.get_material();

    std::cout << "Set material value:" << std:: endl;
    std::cout << get_material_val.color.red << std:: endl;
    std::cout << get_material_val.color.green << std:: endl;
    std::cout << get_material_val.color.blue << std:: endl;

    // Add a light source
    PointLight light = PointLight(point(-10, 10, 10), Color(1, 1, 1));

    // Define the canvas
    unsigned int cam_size = 1024;
    unsigned int canv_x = cam_size, canv_y = cam_size;
    Canvas c(canv_x, canv_y);

    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "New image generation starting!" << std::endl;

    
    Tuple current_point;
    Ray current_ray(camera_origin, bot_left - camera_origin);

    // Track how long the actual loops took
    auto start = high_resolution_clock::now();

    for (int i=0; i < canv_x; i++) {
        for (int j=0; j < canv_y; j++) {
            // Get the new ray
            current_point = bot_left + (right_movement * i / canv_x) + (up_movement * j / canv_y);
            // Normalize the ray
            current_ray = Ray(camera_origin, (current_point - camera_origin).normalize());
            
            // Check if it hit the sphere
            Intersections xs = intersect(&s, current_ray);

            if (xs.count > 0) {
                // Normalize Ray direction and find normal vector at the hit
                Intersection inter = xs.hit();
                Tuple hit_point = current_ray.position(inter.t);
                Tuple norm = inter.object.normal_at(hit_point);

                // Calculate the eye vector
                Tuple eye = - (current_ray.get_direction().normalize());
                
                // Calculate the color with lighting() before applying to the canvas
                // if (i % 80 == 0) {
                //     std::cout << inter.object.get_material().color.red << std:: endl;
                // };
                Color lit_color = inter.object.get_material().lighting(
                    light,
                    hit_point,
                    eye,
                    norm,
                    false
                );
                c.write_pixel(lit_color, i, canv_y - j);
            };
        };
    };
    auto stop = high_resolution_clock::now();

    std::string filename = "transformed_circle.ppm";
    c.write_to_ppm(filename);

    std::cout << "Charted at " << filename << std::endl;

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << " microseconds." << std::endl;
    std::cout << duration.count() / 1000000.0 << " seconds." << std::endl;
    std::cout << duration.count() / (canv_x * canv_y) << " microseconds per pixel." << std::endl;

    return 0;
}
