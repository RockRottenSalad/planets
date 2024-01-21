#version 440 core 

in vec3 o_normal;
in vec3 o_frag;

in vec3 o_sector_stack;
in float o_time;

out vec4 FragColor;

struct light_source
{
    vec3 light_pos;
};

float north_pole(float stack)
{
    return smoothstep(stack+0.15, stack, 0.9);
}

vec3 diffuse_lighting()
{
    vec3 surface_normal = normalize(o_normal);
    vec3 light_pos = vec3(0.0, 1.0, 0.0);
    vec3 light_dir = normalize(o_frag - light_pos);

    float diffuse_strength = max(dot(light_dir, surface_normal), 0.0);
    vec3 diffuse = diffuse_strength * vec3(1.0, 0.9, 0.9);

    return diffuse;
}

void main()
{
    vec3 natural_light = vec3(1.0, 1.0, 1.0);
    float ambient_streng = 0.1;
    vec3 ambient = natural_light * ambient_streng;
    vec3 diffuse = diffuse_lighting();
    
    float is_pole = north_pole(o_sector_stack.y);
    vec3 object_color = (1.0-is_pole)*vec3(0.0, min(0.1, sin(o_sector_stack.x*3.0)), 0.65)+is_pole * vec3(sin(o_sector_stack.y), 1.0, 1.0);

    FragColor = vec4((ambient + diffuse) * object_color, 1.0);
}
