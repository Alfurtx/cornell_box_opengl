#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out VS_OUT {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec4 frag_pos_light_space;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

uniform mat4 light_view;
uniform mat4 light_projection;

void
main()
{
    gl_Position = projection * view * vec4(pos, 1.0f);
    vs_out.color = color;
    vs_out.position = pos;
    vs_out.frag_pos_light_space = light_projection * light_view * vec4(vs_out.position, 1.0f);
    vs_out.normal = normal;
}
