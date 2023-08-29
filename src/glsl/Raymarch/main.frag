#version 450 core

layout(location = 0) in vec2 uvs;
layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = vec4(uvs, 0.5f, 1.0f);
}