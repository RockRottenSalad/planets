
#include "gfx/buffers.hpp"

// VAO

vao_t::vao_t(int buffer_size)
    :size(buffer_size)
{
    glGenVertexArrays(this->size, &this->vao_ptr);
}

vao_t::~vao_t()
{
    glDeleteBuffers(this->size, &this->vao_ptr);
}

void vao_t::bind()
{
    glBindVertexArray(this->vao_ptr);
}

void vao_t::data(int attrib, int vertices, int total_vertices, int offset)
{
    glVertexAttribPointer(attrib, vertices, GL_FLOAT, GL_FALSE, total_vertices*sizeof(float),
            (void*)(sizeof(float)*offset));

    glEnableVertexAttribArray(attrib);
} 

// VBO

vbo_t::vbo_t(int buffer_size)
    :size(buffer_size)
{
    glGenBuffers(this->size, &this->vbo_ptr);
}

vbo_t::~vbo_t()
{
    glDeleteBuffers(this->size, &this->vbo_ptr);
}

void vbo_t::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_ptr);
}

void vbo_t::data(std::vector<glm::vec3> data)
{

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*data.size(), &data.front(), GL_STATIC_DRAW);
} 

// EBO

ebo_t::ebo_t(int buffer_size)
    :size(buffer_size)
{
    glGenBuffers(this->size, &this->ebo_ptr);
}

ebo_t::~ebo_t()
{
    glDeleteBuffers(this->size, &this->ebo_ptr);
}

void ebo_t::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_ptr);
}

void ebo_t::data(std::vector<unsigned int> data)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*data.size(), &data.front(), GL_STATIC_DRAW);
}

