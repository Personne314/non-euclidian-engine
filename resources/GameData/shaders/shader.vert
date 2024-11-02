#version 330 core

in vec3 in_Vertex;

uniform mat4 projection;
uniform mat4 modelview;

void main() {
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
}
