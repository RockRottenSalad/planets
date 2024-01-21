#pragma once

#include <memory>
#include <string>

#include "gfx/shader.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<iostream>
#include<vector>

#include "scene/map.hpp"
#include "utils/camera.hpp"


class window_t
{
    private:
        std::unique_ptr<shader_t> skybox_shader;
        std::unique_ptr<shader_t> shader;

        std::unique_ptr<sphere_t> sphere;
        std::unique_ptr<camera_t> camera;

        glm::ivec2 resolution;
        double delta_time, delta_a, delta_b;

        void event_handler();
        void mouse_handler();
        
    public:
        GLFWwindow* window;

        window_t(std::string const win_title, glm::ivec2 resolution, std::unique_ptr<camera_t> camera);
        ~window_t();

        void set_sphere(std::unique_ptr<sphere_t> sphere);
        void set_shader(std::unique_ptr<shader_t> shader);
        void loop();

};
