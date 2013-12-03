#version 130

in vec3 vertex_position;

out vec3 position;
out vec3 normal;

uniform mat4 mv;
uniform mat4 mvp;
uniform float scale;

void main() {
    normal = normalize(mat3(mvp) * vertex_position);
    position = vec3(mv * vec4(vertex_position, 1));
    gl_Position = mvp * vec4(scale * 0.5 * vertex_position, 1);
}
