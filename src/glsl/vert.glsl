#version 440 core 

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec3 a_sector_stack;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

uniform float e_time;

out vec3 o_sector_stack;
out vec3 o_normal;
out vec3 o_frag;
out float o_time;

void main()
{
    o_sector_stack = a_sector_stack;
    o_normal = a_normal;
    o_frag = a_pos;
    o_time = e_time;

    gl_Position = projection * camera * model * vec4(a_pos, 1.0);
}
