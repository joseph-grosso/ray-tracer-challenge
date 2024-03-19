#include "tuple.h"
#include "material.h"

// Chapter 6: Lights and Shading
Material::Material(
    Color color,
    float ambient,
    float diffuse,
    float specular,
    float shininess
) {
    this->color = color;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
};

// Arithmetic operators
bool operator==(Material lhs, Material rhs) {
    return (
        (lhs.color == rhs.color) &&
        equalByEpsilon(lhs.ambient, rhs.ambient) &&
        equalByEpsilon(lhs.diffuse, rhs.diffuse) &&
        equalByEpsilon(lhs.specular, rhs.specular) &&
        equalByEpsilon(lhs.shininess, rhs.shininess)
    );
};