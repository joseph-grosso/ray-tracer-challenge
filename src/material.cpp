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
