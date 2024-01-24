#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include<iostream>
#include<fstream>
#include<sstream>

class shader_t
{
    private:
        unsigned int ptr;
        std::string vertex_path, frag_path;

        unsigned int camera_unf;
        unsigned int time_unf;
        std::string read_shader(std::string file_path);
    public:
        shader_t(std::string vertex_path, std::string frag_path);
        ~shader_t();
        void compile();
        void use();

        void set_uniform_m4(float* mat, std::string uniform);
        void set_uniform_camera(float* mat);
        void set_uniform_time();
};
