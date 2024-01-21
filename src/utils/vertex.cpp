
#include "utils/vertex.hpp"

vertex_t::vertex_t()
{}

vertex_t::vertex_t(glm::vec3 position_arg, glm::vec3 normal_arg)
    :position(position_arg), normal(normal_arg)
{}
