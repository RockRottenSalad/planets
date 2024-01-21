
#include "gfx/window.hpp"
#include "gfx/shader.hpp"
#include <GLFW/glfw3.h>

window_t::window_t(std::string const win_title, glm::ivec2 resolution, std::unique_ptr<camera_t> camera)
    :camera(std::move(camera)), resolution(resolution) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    this->window = glfwCreateWindow(this->resolution.x, this->resolution.y,
        win_title.c_str(), NULL, NULL); 
    if(this->window == NULL)
        std::cout << "WINDOW IS NULL\n";

    glfwMakeContextCurrent(this->window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "glad ate shit\n";


    glViewport(0, 0, this->resolution.x, this->resolution.y);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int monitor_x, monitor_y;
    glfwGetMonitorWorkarea(monitor, NULL, NULL, &monitor_x, &monitor_y);
    glfwSetWindowPos(this->window, (monitor_x/2) + this->resolution.x, (monitor_y/2));
}

window_t::~window_t()
{
    glfwTerminate();
}

void window_t::event_handler()
{
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);

    if(glfwGetKey(this->window, GLFW_KEY_W))
        this->camera->move_forward();

    if(glfwGetKey(this->window, GLFW_KEY_S))
        this->camera->move_back();

    if(glfwGetKey(this->window, GLFW_KEY_D))
        this->camera->move_right();

    if(glfwGetKey(this->window, GLFW_KEY_A))
        this->camera->move_left();

    return;
}

void window_t::mouse_handler()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y); 
    this->camera->rotate(x, y);
}


void window_t::set_sphere(std::unique_ptr<sphere_t> sphere)
{
    this->sphere = std::move(sphere);
}

void window_t::set_shader(std::unique_ptr<shader_t> shader)
{
    this->shader = std::move(shader);
}

void window_t::loop()
{
    this->delta_a = this->delta_b = glfwGetTime();
    GLenum err;

    while(!glfwWindowShouldClose(this->window))
    {
        this->delta_b = glfwGetTime();
        this->delta_time = this->delta_b - this->delta_a;
        this->camera->dt = this->delta_time;

        err = glGetError();
        if(err != GL_NO_ERROR)
            std::cout << "ERROR CODE: " << err << "\n";

        if(this->delta_time >= 1.0 / 60.0)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->mouse_handler();
            this->camera->update_camera();
            this->shader->set_uniform_camera(camera->get_mat());
            this->shader->set_uniform_time();
            glDrawElements(GL_TRIANGLES, this->sphere->indices.size(), GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(this->window);
            
            this->delta_a = this->delta_b;
        }

        glfwPollEvents();
        this->event_handler();
    }

    return;
}

