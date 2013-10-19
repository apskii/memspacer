#version 400 core

layout (location = 0) in vec3 vertex_position;

uniform mat4 view_proj;

void main() {
    gl_Position = view_proj * vec4(vertex_position, 1);
}