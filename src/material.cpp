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

std::string Material::to_string() {
    return "Material(Color=" + color.to_string() +
        ", Ambient=" + std::to_string(ambient) +
        ", Diffuse=" + std::to_string(diffuse) +
        ", Specular=" + std::to_string(specular) +
        ", Shininess=" + std::to_string(shininess) + ")";
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