#version 330

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_texcoord;
layout(location = 2) in vec3 i_normal;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;

out vec2 v_texcoord;

void main() {
    mat4 m_view = mat4(u_view);
    m_view[3][0] = 0;
    m_view[3][1] = 0;
    m_view[3][2] = 0;

    gl_Position = u_proj * m_view * u_model * vec4(i_vertex, 1);
    v_texcoord = i_texcoord;
}