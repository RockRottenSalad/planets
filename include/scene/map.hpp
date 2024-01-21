#pragma once

#include <memory>
#include "utils/object_assembler.hpp"

using objasm::sphere_t;

class map_t
{
    private:
        std::vector<sphere_t*> sphere_list;
    public:
        map_t();
        ~map_t();

        std::vector<glm::vec3> batch_spheres();

};
