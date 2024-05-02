#include "ray_tracer.h"
#include "gtest/gtest.h"
#include <math.h>
#include <gmock/gmock.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>


// Fixture: Set up the material and positions
// p86
class TestShadows : public testing::Test {
    protected:
        Material m = Material();
        Tuple position = point(0, 0, 0);
};

// Scenario: Lighting with the surface in shadow
// p110
TEST_F (TestShadows, SurfaceInShadow) {
    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    bool in_shadow = true;

    Color result = m.lighting(light, position, eyev, normalv, in_shadow);

    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

// TEST_F (TestSphereReflection, LightingWithEyeBetweenLightAndSurface) {
//     Tuple eyev = vector(0, 0, -1);
//     Tuple normalv = vector(0, 0, -1);
//     PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

//     Color result = m.lighting(light, position, eyev, normalv);
    
//     EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
// }