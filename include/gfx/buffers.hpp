#pragma once

#include <vector>
#include<iostream>

#include "utils/vertex.hpp"
#include "glad/glad.h"

class vao_t
{
    private:
        unsigned int vao_ptr, size;
    public:
        vao_t(int buffer_size);
        ~vao_t();
        void bind();
        void data(int attrib, int vertices, int total_vertices, int offset);
};

class vbo_t
{
    private:
        unsigned int vbo_ptr, size;
    public:
        vbo_t(int buffer_size);
        ~vbo_t();
        void bind();
        void data(std::vector<glm::vec3> data);
};

class ebo_t
{
    private:
        unsigned int ebo_ptr, size;
    public:
        ebo_t(int buffer_size);
        ~ebo_t();
        void bind();
        void data(std::vector<unsigned int> data);
};
