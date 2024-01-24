
#include "utils/camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>


camera_t::camera_t()
{
    this->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->speed = 0.0025f;
    this->sensitivity = 0.5f;
    this->last_x = this->last_y = 450.0;

    this->look_at = glm::lookAt(this->position, this->direction+this->position, this->up);
}

camera_t::~camera_t()
{}

void camera_t::update_camera()
{
    this->look_at = glm::lookAt(this->position, this->direction+this->position, this->up);
}

void camera_t::move_forward()
{
    this->direction = glm::normalize(this->direction);
    glm::vec3 movement = this->direction*(this->speed*this->dt);
    this->position += movement;
}

void camera_t::move_back()
{
    this->direction = glm::normalize(this->direction);
    glm::vec3 movement = this->direction*(this->speed*this->dt);
    this->position -= movement;
}

void camera_t::move_right()
{
//    this->direction = glm::normalize(this->direction);
    glm::vec3 movement = glm::cross(direction, up);
    movement = glm::normalize(movement);
    movement *= this->speed*this->dt;
    this->position += movement;
}

void camera_t::move_left()
{
    glm::vec3 movement = glm::cross(direction, up);
    movement = glm::normalize(movement);
    movement *= this->speed*this->dt;
    this->position -= movement;
}

void camera_t::rotate(double x, double y)
{
    yaw += (x - this->last_x) * this->sensitivity;
    pitch += (this->last_y - y) * this->sensitivity;
    this->last_x = x;
    this->last_y = y;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    this->direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->direction.y = sin(glm::radians(pitch));
    this->direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->direction = glm::normalize(this->direction);
}

void camera_t::lock()
{
    this->speed = 0.0f;
    this->sensitivity = 0.0f;
}

void camera_t::unlock()
{
    this->speed = 0.0025f;
    this->sensitivity = 0.5f;
}

float* camera_t::get_mat()
{
    return glm::value_ptr(this->look_at);
}
