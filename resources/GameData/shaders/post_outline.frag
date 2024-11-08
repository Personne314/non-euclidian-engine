#version 450 core

in vec2 tex_coord;
out vec4 out_color;

uniform vec2 pixel_size;
uniform sampler2D pixel_buffer;
uniform sampler2D depth_buffer;


void main() {

	out_color = texture(pixel_buffer, tex_coord);

	float depthLeft = texture(depth_buffer, tex_coord + vec2(-pixel_size.x, 0.0)).r;
    float depthRight = texture(depth_buffer, tex_coord + vec2(pixel_size.x, 0.0)).r;
    float depthUp = texture(depth_buffer, tex_coord + vec2(0.0, pixel_size.y)).r;
    float depthDown = texture(depth_buffer, tex_coord + vec2(0.0, -pixel_size.y)).r;

    float gradientX = depthRight - depthLeft;
    float gradientY = depthUp - depthDown;
	if (gradientX * gradientX + gradientY * gradientY > 1e-8) out_color = vec4(0.0,0.0,0.0,1.0);

}
