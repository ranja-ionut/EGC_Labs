#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform int spot;
uniform float angle;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 R = reflect(-L, N);

	float ambient_light = 0.25;

	float diffuse_light = material_kd * max (dot(N,L), 0);

	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = pow(max(0, dot(R, V)), material_shininess) * material_ks;
	}

	float light = 0;

	if (spot == 1) {
		float cut_off = radians(angle);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off);

		if (spot_light > spot_light_limit)
		{
			// Quadratic attenuation
			float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);

			light = ambient_light + light_att_factor * max(diffuse_light + specular_light, 0);
		} else {
			light = ambient_light;
		}
	} else {
		light = ambient_light + max(diffuse_light + specular_light, 0);
	}

	out_color = vec4(light * object_color, 1);
}