#pragma once

#include <vector>


class Intersection {
    private:
        std::vector<float> points;
        unsigned int count;
    public:
        Intersection(std::vector<float>);
        unsigned int get_count();
        float get_point(unsigned int i);
        float operator[](int i);
};