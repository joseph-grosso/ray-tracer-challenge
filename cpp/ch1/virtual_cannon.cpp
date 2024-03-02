#include <iostream>
#include <cmath>
#include <iomanip>

#include "tuple.h"

using namespace std;

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

int main() {
    int tick_count = 0;
    Tuple pos = point(0, 1, 0);
    Tuple vel = vector(1, 1, 0);

    Tuple grav = vector(0, -0.1, 0);
    Tuple wind = vector(-0.01, 0, 0);

    Projectile p = Projectile(pos, vel);
    Environment e(grav, wind);

    cout << setprecision(2) << fixed;
    cout << "New flight starting!" << endl;

    while (p.position.y > 0) {
        cout << " x: " << p.position.x << "\t";
        cout << "|y: " << p.position.y << "\t";
        cout << "|z: " << p.position.z << "\t" << endl;
        p = tick_projectile(e, p);
    };

    cout << "New flight ending!" << endl;

    return 0;
}


Projectile::Projectile(Tuple position, Tuple velocity) {
        this->position = position;
        this->velocity = velocity;
};