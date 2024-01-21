#pragma once

#include "utils/vertex.hpp"

#include <cmath>
#include <vector>

namespace objasm
{
    struct sphere_t
    {
        std::vector<vertex_t> vertices;
        std::vector<unsigned int> indices;
        float radius;

        void make_sphere(float radius);
        std::vector<glm::vec3> format_data();
    };

};
