#version 130

in vec3 position;
in vec3 normal;

out vec4 frag_color;

uniform vec3 light_position;
uniform vec3 light_intensity;
uniform vec4 color;
uniform vec3 k_diffuse;
uniform vec3 k_ambient;
uniform vec3 k_specular;
uniform float shininess;

vec3 ads() {
    vec3 n = normalize(normal);
    vec3 s = normalize(light_position - position);
    vec3 v = normalize(vec3(-position));
    vec3 r = reflect(-s, n);
    return light_intensity * (
        k_ambient +
        k_diffuse * max(dot(s, n), 0.0) +
        k_specular * pow(max(dot(r, v), 0.0), shininess)
    );
}

void main() {
    frag_color = vec4(ads(), 1);
}
