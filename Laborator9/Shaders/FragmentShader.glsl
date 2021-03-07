#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int usesTexture2;
uniform float time;
uniform int isGlobe;

in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	if (isGlobe == 1) {
		out_color = texture2D(texture_1, texcoord + vec2(time, 0));
	} else {
		out_color = texture2D(texture_1, texcoord);
	}

	if (out_color.a < 0.5) {
		discard;
	}

	if (usesTexture2 == 1) {
		vec4 color2 = texture2D(texture_2, texcoord);
		out_color = mix(out_color, color2, 0.5);
	}
}

float myMix(float V1, float V2, float f) {
	return (1 - f) * V1 + f * V2;
}