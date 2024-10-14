#include "lights.h"

// Chapter 6: Lights and Shading
PointLight::PointLight(Tuple position, Color intensity) {
  this->position = position;
  this->intensity = intensity;
};

Tuple PointLight::get_position() { return position; };
Color PointLight::get_intensity() { return intensity; };
