#include "ray_tracer.h"
#include "gtest/gtest.h"

#include <cmath>
#include <string>
#include <vector>
#include <iostream>


// Scenario: Creating a world
// p92
TEST (TestWorld, CreatingAWorld) {
    World w = World();

    EXPECT_EQ(w.objects.size(), 0);
    EXPECT_EQ(w.lights.size(), 0);
}

// Scenario: Creating a default world
// p92
TEST (TestWorld, DefaultWorld) {

    PointLight light = point_light(point(-10, 10, -10), Color(1, 1, 1))
    Sphere s1 = Sphere();
    s1.set_material(
        Material(
            Color(0.8, 1.0, 0.6),  // color
            0.1,  // ambient
            0.7,  // diffuse
            0.2,  // specular
            200.0  // shininess
        )
    );
    Sphere s2 = Sphere();
    s2.set_transform(scaling_matrix(0.5, 0.5, 0.5));

    World w = default_world();

    EXPECT_THAT(w.objects, Contains(s1));
    EXPECT_THAT(w.objects, Contains(s2));
    // EXPECT_EQ(w.lights.size(), );
}
