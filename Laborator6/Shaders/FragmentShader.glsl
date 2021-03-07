#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;

uniform float time;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(frag_normal * (sin(time) * 0.5 + 0.5) + vec3(1, 0, 0), 1);
}