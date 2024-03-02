#include <iostream>
#include <cmath>
#include <iomanip>

#include "tuple.h"
#include "canvas.h"


// using namespace std;

class Projectile {
    public:
        // Attributes
        Tuple position;
        Tuple velocity;
        // Methods
        Projectile(Tuple position, Tuple velocity);
};

class Environment {
    public:
        // Attributes
        Tuple gravity;
        Tuple wind;
        // Methods
        Environment(Tuple gravity, Tuple wind) {
            this->gravity = gravity;
            this->wind = wind;
        };
};

Projectile tick_projectile(Environment env, Projectile proj) {
    Tuple new_position = proj.position + proj.velocity;
    Tuple new_velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(new_position, new_velocity);
}

// void fill_in_canvas_at_position(Canvas c, int x, int y) {
//     cout << "Filling canvas at position" << endl;
//     cout << "i value: " << to_string(x) << endl;
//     cout << "j value: " << to_string(y) << endl;
//     for (int i = x; i<=x+5; i++) {
//         for (int j = y; j<=y+5; j++) {
//             if (i >= 0 && i < c.get_width() && j >= 0 && j < c.get_height()) {
//                 c.write_pixel(Color(1, 0, 0), x, c.get_height() - y);
//             };
//         };
//     };
// }

int main() {
    int tick_count = 0;
    Tuple pos = point(0, 1, 0);
    Tuple vel = vector(1, 1.8, 0).normalize() * 11.25;

    Tuple grav = vector(0, -0.1, 0);
    Tuple wind = vector(-0.01, 0, 0);

    Projectile p = Projectile(pos, vel);
    Environment e(grav, wind);

    Canvas c(900, 500);

    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "New flight starting!" << std::endl;

    while (p.position.y > 0) {
        // fill_in_canvas_at_position(c, (int) p.position.x, (int) p.position.y);
        std::cout << "Filling canvas at position" << std::endl;
        std::cout << "i value: " << std::to_string(p.position.x) << std::endl;
        std::cout << "j value: " << std::to_string(p.position.y) << std::endl;
        for (int i = (int) p.position.x; i<=(int) p.position.x+5; i++) {
            for (int j = (int) p.position.y; j<=(int) p.position.y+5; j++) {
                if (i >= 0 && i < c.get_width() && j >= 0 && j < c.get_height()) {
                    c.write_pixel(Color(1, 0, 0), i, c.get_height() - j);
                };
            };
        };
        p = tick_projectile(e, p);
    };

    std::cout << "New flight ending!" << std::endl;

    
    c.write_to_ppm("flight_path.ppm");

    std::cout << "Charted at flight_path.ppm" << std::endl;


    return 0;
}


Projectile::Projectile(Tuple position, Tuple velocity) {
        this->position = position;
        this->velocity = velocity;
};