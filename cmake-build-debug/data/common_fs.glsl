#version 330

const int c_numLights = 5;
const float c_ambient = 0.5;

in vec2 v_texcoord;
in vec3 v_normal;
in vec3 v_tolight[c_numLights];

uniform sampler2D sampler;
uniform vec3 u_lightcolors[c_numLights];
uniform float u_lightstrengths[c_numLights];

out vec4 o_color;

void main(){
    vec4 diffuse = vec4(0);

    for(int i = 0; i < c_numLights; i++){
        if(u_lightstrengths[i] == 0) continue;
        float dis = length(v_tolight[i]);
        //float attenuation = max(1 / (1 + u_lightstrengths[i] * 0.009f * dis * dis - 0.003f * dis * dis * dis), 0);
        float attenuation = inversesqrt(dis) * u_lightstrengths[i];

        float b = max(dot(v_normal, normalize(v_tolight[i])), 0);
        diffuse += vec4(normalize(u_lightcolors[i]) * b * attenuation, 1);
    }

    diffuse = max(diffuse, c_ambient);
    diffuse.a = 1;
    o_color = diffuse * texture(sampler, v_texcoord);
    //if(o_color.a < 0.9) discard;
}
