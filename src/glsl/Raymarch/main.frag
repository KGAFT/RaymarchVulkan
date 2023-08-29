#version 450 core

layout(location = 0) in vec2 tr;
layout(location = 0) out vec4 FragColor;

layout(push_constant) uniform CodeInput{
    vec2 resolution;
} input;

vec3 render(vec2 UV){
    vec3 res = vec3(UV, 0);
    return res;
}

void main() {
    vec2 uv = (2.0*gl_FragCoord.xy-input.resolution)/input.resolution.y;

    FragColor = vec4(render(uvs), 1.0f);
}