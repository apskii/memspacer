#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4  mvp;
uniform float scale;

void main() {
    gl_Position = mvp * vec4(scale * 0.5 * vertexPosition_modelspace, 1);
}