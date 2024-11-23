#version 450 core

in vec3 in_coord;
in vec3 in_color;
out vec3 color; 

uniform mat4 projection;
uniform mat4 modelview;

void main() {
	gl_Position = projection * modelview * vec4(in_coord, 1.0);
	color = in_color;
}
