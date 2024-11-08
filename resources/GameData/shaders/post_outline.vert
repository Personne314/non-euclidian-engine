#version 450 core

in vec2 in_coord;
in vec2 in_tex_coord;
out vec2 tex_coord;

void main() {
	gl_Position = vec4(in_coord, 0.0, 1.0);
	tex_coord = in_tex_coord;
}
