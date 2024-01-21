
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

#include "gfx/window.hpp"
#include "gfx/buffers.hpp"
#include "gfx/shader.hpp"
#include "utils/object_assembler.hpp"
#include "utils/camera.hpp"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// what is this?
// todo: fix whatever the hell this is

int main()
{
    std::unique_ptr<camera_t> camera (new camera_t());
    std::unique_ptr<window_t> window (new window_t("GLSL test", glm::ivec2(900,900), std::move(camera)));

    std::unique_ptr<objasm::sphere_t> sphere (new objasm::sphere_t());
    sphere->make_sphere(0.5f);
    std::cout << sphere->indices.size() << "\n";

    std::unique_ptr<vao_t> vao (new vao_t(1));
    vao->bind();
    std::unique_ptr<vbo_t> vbo (new vbo_t(1));
    vbo->bind();
    vbo->data(sphere->format_data());

    // attrib, vertices, total vertices, offset
    vao->data(0, 3, 9, 0);
    vao->data(1, 3, 9, 3);
    vao->data(2, 3, 9, 6);

    std::unique_ptr<ebo_t> ebo (new ebo_t(1));
    ebo->bind();
    ebo->data(sphere->indices);

    std::unique_ptr<shader_t> shader (new shader_t("src/glsl/vert.glsl", "src/glsl/frag.glsl"));
    shader->use();

    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::perspective(3.14f/2.0f, 1.0f, 0.01f, 100.0f);
    shader->set_uniform_m4(glm::value_ptr(mat), "projection");

    mat = glm::mat4(1.0f);
    mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    shader->set_uniform_m4(glm::value_ptr(mat), "model");

    window->set_sphere(std::move(sphere));
    window->set_shader(std::move(shader));
    glEnable(GL_DEPTH_TEST);
    window->loop();

    return 0;
}

