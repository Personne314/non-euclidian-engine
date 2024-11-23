#version 450 core

in vec2 tex_coord;
out vec4 out_color;

uniform vec2 pixel_size;
uniform sampler2D pixel_buffer;
uniform sampler2D depth_buffer;


void main() {

	float depth = texture(depth_buffer, tex_coord).r;
	float depthLeft = texture(depth_buffer, tex_coord + vec2(-pixel_size.x, 0.0)).r;
	float depthRight = texture(depth_buffer, tex_coord + vec2(pixel_size.x, 0.0)).r;
	float depthUp = texture(depth_buffer, tex_coord + vec2(0.0, pixel_size.y)).r;
	float depthDown = texture(depth_buffer, tex_coord + vec2(0.0, -pixel_size.y)).r;

	vec4 color = texture(pixel_buffer, tex_coord);
	vec4 colorLeft = texture(pixel_buffer, tex_coord + vec2(-pixel_size.x, 0.0));
	vec4 colorRight = texture(pixel_buffer, tex_coord + vec2(pixel_size.x, 0.0));
	vec4 colorUp = texture(pixel_buffer, tex_coord + vec2(0.0, pixel_size.y));
	vec4 colorDown = texture(pixel_buffer, tex_coord + vec2(0.0, -pixel_size.y));

    bool depthChange = abs(depthLeft + depthRight + depthDown + depthUp - 4.0 * depth) > 1e-6;
    vec4 colorDiff = max(abs(color - colorLeft), max(abs(color - colorRight),
		max(abs(color - colorUp), abs(color - colorDown))));
	bool colorChange = any(greaterThan(colorDiff.rgb, vec3(0.01)));

	out_color = texture(pixel_buffer, tex_coord);
	if (depthChange || colorChange) out_color = vec4(0.0,0.0,0.0,1.0);

}
