#include <vector>
#include "intersection.h"


Intersection::Intersection(std::vector<float> points) {
    this->count = points.size();
    this->points = points;
};

float Intersection::get_point(unsigned int i) {
    return points[i];
};

unsigned int Intersection::get_count() {
    return count;
};

float Intersection::operator[](int i) {
    float out = get_point(i);
    float *out_ptr = &out;
    return *out_ptr;
};
