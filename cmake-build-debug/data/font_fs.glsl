#version 330

in vec2 v_texcoord;

uniform sampler2D sampler;

out vec4 o_color;

void main(){
    vec4 c = texture(sampler, v_texcoord);
    float a = c.x;
    if(a == 0) discard;
    o_color = vec4(1, 1, 1, a);
}
