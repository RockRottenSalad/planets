
#include "gfx/shader.hpp"
#include <GLFW/glfw3.h>


std::string shader_t::read_shader(std::string file_path)
{
    std::ifstream fd(file_path);
    std::stringstream buffer;
    buffer << fd.rdbuf();

    return buffer.str();
}

shader_t::shader_t(std::string vertex_path, std::string frag_path)
{
    unsigned int vertex_shader, fragment_shader;
    std::string src;
    const char* c_str;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    src = this->read_shader(vertex_path);
    glShaderSource(vertex_shader, 1, &(c_str = src.c_str()), NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    src = this->read_shader(frag_path);
    glShaderSource(fragment_shader, 1, &(c_str = src.c_str()), NULL);
    glCompileShader(vertex_shader);

    this->ptr = glCreateProgram();
    glAttachShader(this->ptr, vertex_shader);
    glAttachShader(this->ptr, fragment_shader);
    glLinkProgram(this->ptr);

    int check;
    glGetProgramiv(this->ptr, GL_LINK_STATUS, &check);
    if(!check)
    {
        glGetProgramInfoLog(this->ptr, 256, NULL, src.data());
        std::cout << src << "\n";
    }

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    this->camera_unf = glGetUniformLocation(this->ptr, "camera");
    this->time_unf = glGetUniformLocation(this->ptr, "e_time");

//    this->projection_unf = glGetUniformLocation(this->ptr, "projection");
}

shader_t::~shader_t()
{
    glDeleteProgram(this->ptr);
}

void shader_t::use()
{
    glUseProgram(this->ptr);
}

void shader_t::set_uniform_m4(float* mat, std::string uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ptr, uniform.c_str()), 1, GL_FALSE, mat);

}

void shader_t::set_uniform_camera(float* mat)
{
    glUniformMatrix4fv(this->camera_unf, 1, GL_FALSE, mat);
}

void shader_t::set_uniform_time()
{
    glUniform1f(this->time_unf, static_cast<float>(glfwGetTime()));
}
