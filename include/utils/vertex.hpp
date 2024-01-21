#pragma once

#include<glm/glm.hpp>

#include<vector>

struct vertex_t
{
    glm::vec3 position;
    glm::vec3 normal;
    float sector_index;
    float stack_index;
    vertex_t();
    vertex_t(glm::vec3 position_arg, glm::vec3 normal_arg);
};
