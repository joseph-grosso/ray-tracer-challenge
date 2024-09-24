#include "material.h"


// Chapter 6: Lights and Shading
Material::Material(
    StripePattern * pattern,
    Color color,
    float ambient,
    float diffuse,
    float specular,
    float shininess
) {
    this->pattern = pattern;
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

Color Material::lighting(
    PointLight light,
    Tuple position,
    Tuple eyev,
    Tuple normalv,
    bool in_shadow
) {
    Color black = Color();
    Color effective_color = this->color * light.get_intensity();
    Tuple lightv = (light.get_position() - position).normalize();

    Color ambient = effective_color * this->ambient;

    if (in_shadow) {
        return ambient;
    };

    Color diffuse, specular;

    float light_dot_normal = lightv.dot(normalv);
    if (light_dot_normal < 0) {
        diffuse = black;
        specular = black;
    } else {
        diffuse = effective_color * this->diffuse * light_dot_normal;
        Tuple reflectv = (-lightv).reflect(normalv);
        float reflect_dot_eye = reflectv.dot(eyev);
        
        if (reflect_dot_eye <= 0) {
            specular = black;
        } else {
            float factor = std::pow(reflect_dot_eye, this->shininess);
            specular = light.get_intensity() * this->specular * factor;
        };
    };

    return ambient + diffuse + specular;
};

// Arithmetic operators
bool operator==(Material lhs, Material rhs) {
    return (
        (lhs.pattern == rhs.pattern) &&
        (lhs.color == rhs.color) &&
        equalByEpsilon(lhs.ambient, rhs.ambient) &&
        equalByEpsilon(lhs.diffuse, rhs.diffuse) &&
        equalByEpsilon(lhs.specular, rhs.specular) &&
        equalByEpsilon(lhs.shininess, rhs.shininess)
    );
};