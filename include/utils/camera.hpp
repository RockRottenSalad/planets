#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


class camera_t
{
    private:
        glm::vec3 direction;
        glm::vec3 position;
        glm::vec3 up;
        glm::mat4 look_at;

        float sensitivity, speed;
        double pitch, yaw, last_x, last_y;

    public:
        camera_t();
        ~camera_t();

        float dt;
        void update_camera();
        void move_forward();
        void move_back();
        void move_right();
        void move_left();
        void rotate(double,double);
        void lock();
        void unlock();

        float* get_mat();
};
