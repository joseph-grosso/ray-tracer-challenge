#include "tuple.h"
#include "lights.h"
#include "material.h"

#include <cmath>

// Chapter 6: Lights and Shading

PointLight::PointLight(Tuple position, Color intensity) {
    this->position = position;
    this->intensity = intensity;    
};

Tuple PointLight::get_position() {
    return position;
};
Color PointLight::get_intensity() {
    return intensity;
};

Color lighting(
    Material material,
    PointLight light,
    Tuple position,
    Tuple eyev,
    Tuple normalv
) {
    Color black = Color();
    Color effective_color = material.color * light.get_intensity();
    Tuple lightv = (light.get_position() - position).normalize();

    Color ambient = effective_color * material.ambient;

    Color diffuse, specular;

    float light_dot_normal = lightv.dot(normalv);
    if (light_dot_normal < 0) {
        diffuse = black;
        specular = black;
    } else {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        Tuple reflectv = (-lightv).reflect(normalv);
        float reflect_dot_eye = reflectv.dot(eyev);
        
        if (reflect_dot_eye <= 0) {
            specular = black;
        } else {
            float factor = std::pow(reflect_dot_eye, material.shininess);
            specular = light.get_intensity() * material.specular * factor;
        };
    };
    return ambient + diffuse + specular;
};
