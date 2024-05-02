#include <string>
#include <vector>
#include <iostream>
#include "tuple.h"
#include "matrix.h"
#include "transform.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
#include "lights.h"
#include "material.h"
#include "gtest/gtest.h"

#include <cmath>


// Scenario: Normal of a sphere at the X axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtX) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(1, 0, 0);

    EXPECT_EQ(n, vector(1, 0, 0));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at the Y axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtY) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(0, 1, 0);

    EXPECT_EQ(n, vector(0, 1, 0));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at the Z axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtZ) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(0, 0, 1);

    EXPECT_EQ(n, vector(0, 0, 1));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfSphereAtNonAxis) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3);

    EXPECT_EQ(n, vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfTranslatedSphere) {
    Sphere s = Sphere();
    s.set_transform(translation_matrix(0, 1, 0));
    Tuple n = s.normal_at(0, 1.70711, -0.70711);

    EXPECT_EQ(n, vector(0, 0.70711, -0.70711));
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfTransformedSphere) {
    Sphere s = Sphere();
    s.set_transform(scaling_matrix(1, 0.5, 1) * rotation_z_matrix(M_PI/5));

    Tuple n = s.normal_at(0, std::sqrt(2)/2, -std::sqrt(2)/2);

    EXPECT_EQ(n, vector(0, 0.97014, -0.24254));
}

// Scenario: Reflect a vector in a normal approaching at 45 deg.
// p83
TEST (TestLightingAndShading, ReflectInNormal) {
    Tuple v = vector(1, -1, 0);
    Tuple n = vector(0, 1, 0);
    EXPECT_EQ(v.reflect(n), vector(1, 1, 0));
}

// Scenario: Reflect a vector off a slanted surface.
// p83
TEST (TestLightingAndShading, ReflectInSlantedSurface) {
    Tuple v = vector(0, -1, 0);
    Tuple n = vector(std::sqrt(2)/2, std::sqrt(2)/2, 0);
    EXPECT_EQ(v.reflect(n), vector(1, 0, 0));
}

// Scenario: Creating a point light
// p84
TEST (TestLightingAndShading, CreatePointLight) {
    Tuple position = point(1, 1, 1);
    Color intensity = Color(1, 1, 1);
    
    PointLight light = PointLight(position, intensity);

    EXPECT_EQ(light.get_position(), position);
    EXPECT_EQ(light.get_intensity(), intensity);
}

// Scenario: A material has default settings
// p85
TEST (TestLightingAndShading, CreateDefaultMaterial) {
    Material m = Material();

    EXPECT_EQ(m.color, Color(1, 1, 1));
    EXPECT_TRUE(equalByEpsilon(m.ambient, 0.1));
    EXPECT_TRUE(equalByEpsilon(m.diffuse, 0.9));
    EXPECT_TRUE(equalByEpsilon(m.specular, 0.9));
    EXPECT_TRUE(equalByEpsilon(m.shininess, 200.0));
}

// Scenario: A sphere has a default material
// p85
TEST (TestLightingAndShading, SphereHasDefaultMaterial) {
    Material m = Material();
    Sphere s = Sphere();
    EXPECT_EQ(m, s.get_material());
}

// Scenario: A sphere has a material that can be set
// p85
TEST (TestLightingAndShading, SphereMaterialCanBeSet) {
    Material m = Material();
    Sphere s = Sphere();

    m.ambient = 1;
    s.set_material(m);

    EXPECT_EQ(m, s.get_material());
}

// Fixture: Set up the material and positions
// p86
class TestSphereReflection : public testing::Test {
    protected:
        Material m = Material();
        Tuple position = point(0, 0, 0);
};

// Scenario: Lighting with the eye between the light and the surface
// p86
TEST_F (TestSphereReflection, LightingWithEyeBetweenLightAndSurface) {
    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

// Scenario: Lighting with the eye between the light and the surface, offset at a 45 degree angle
// p86
TEST_F (TestSphereReflection, LightingWithEyeBetweenAt45Degree) {
    Tuple eyev = vector(0, std::sqrt(2)/2, -std::sqrt(2)/2);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

// Scenario: Lighting with the eye between the light and the surface, view offset at a 45 degree angle
// p86
TEST_F (TestSphereReflection, LightingWithEyeAt45Degree) {
    Tuple eyev = vector(0, std::sqrt(2)/2, -std::sqrt(2)/2);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

// Scenario: Lighting with the eye between the light and the surface, light offset at a 45 degree angle
// p87
TEST_F (TestSphereReflection, LightingWithLightAt45Degree) {
    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

// Scenario: Lighting with bot eye and light at 45 degrees to the surface
// p87
TEST_F (TestSphereReflection, LightingWithBothAt45Degree) {
    Tuple eyev = vector(0, -std::sqrt(2)/2, -std::sqrt(2)/2);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(1.63639, 1.63639, 1.63639));
}

// Scenario: Lighting behind the surface
// p88
TEST_F (TestSphereReflection, LightingBehindSurface) {
    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, 10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    
    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}