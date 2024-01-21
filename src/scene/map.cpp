
#include "scene/map.hpp"

map_t::map_t()
{
    sphere_t* sphere = new sphere_t; 
    sphere->make_sphere(0.25f);
    this->sphere_list.push_back(sphere);
}

map_t::~map_t()
{
    for(sphere_t* sphere : this->sphere_list)
    {
        delete sphere;
    }
}

std::vector<glm::vec3> map_t::batch_spheres()
{
    std::vector<glm::vec3> batch;
    std::vector<glm::vec3> tmp;

    for(sphere_t* sphere : this->sphere_list)
    {
        tmp = sphere->format_data();
        batch.insert(batch.end(), tmp.begin(), tmp.end());
    }

    return batch;
}
