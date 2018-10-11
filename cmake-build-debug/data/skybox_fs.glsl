#version 330

const float c_ambient = 0.8;

in vec2 v_texcoord;

uniform sampler2D sampler;

out vec4 o_color;

void main(){
    vec4 diffuse = vec4(c_ambient);
    diffuse.a = 1;
    o_color = diffuse * texture(sampler, v_texcoord);
}
