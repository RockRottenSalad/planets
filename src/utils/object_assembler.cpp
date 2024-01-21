
#include "utils/object_assembler.hpp"
#include "utils/vertex.hpp"


void objasm::sphere_t::make_sphere(float radius)
{
    this->vertices.clear();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, length_inv = 1.0f / radius;    // vertex normal

    float stack_count = 12.0f;
    float sector_count = 16.0f;


    float sector_step = 2.0f * M_PI / sector_count;
    float stack_step = M_PI / stack_count;
    float sector_angle, stack_angle;

    for(int i = 0; i <= stack_count; ++i)
    {
        stack_angle = M_PI / 2.0f - i * stack_step;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stack_angle);             // r * cos(u)
        z = radius * sinf(stack_angle);              // r * sin(u)

        // add (sector_count+1) vertices per stack
        // first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sector_count; ++j)
        {
            vertex_t vertex;
            sector_angle = j * sector_step;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sector_angle);             // r * cos(u) * cos(v)
            y = xy * sinf(sector_angle);             // r * cos(u) * sin(v)
            vertex.position.x = x; 
            vertex.position.y = y; 
            vertex.position.z = z; 

            // normalized vertex normal (nx, ny, nz)
            nx = x * length_inv;
            ny = y * length_inv;
            nz = z * length_inv;

            vertex.normal.x = nx;
            vertex.normal.y = ny;
            vertex.normal.z = nz;

            vertex.sector_index = static_cast<float>(j) / sector_count;
            vertex.stack_index = static_cast<float>(i) / stack_count;

            this->vertices.push_back(vertex);
        }
    }

    int k1, k2;
    for(int i = 0; i < stack_count; ++i)
    {
        k1 = i * (sector_count + 1);     // beginning of current stack
        k2 = k1 + sector_count + 1;      // beginning of next stack

        for(int j = 0; j < sector_count; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stack_count-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

        }
    }

}

std::vector<glm::vec3> objasm::sphere_t::format_data()
{
    std::vector<glm::vec3> formatted_data;

        for(vertex_t vertex : this->vertices)
        {
            formatted_data.push_back(vertex.position);
            formatted_data.push_back(vertex.normal);
            formatted_data.push_back(glm::vec3(vertex.sector_index, vertex.stack_index, 0.0));
        }

    return formatted_data;
}
