#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// TODO: compute world space vectors
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 N = normalize( mat3(Model) * v_normal);
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );

	// TODO: define ambient light component
	float ambient_light = 0.15;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max (dot(N,L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	float d = distance(world_pos, light_position);

	float atenuare = 1 / (0.05 + 0.07 * d + 0.1 * d * d);

	if (diffuse_light > 0)
	{
		vec3 R = reflect(-L, N);
		specular_light = pow(max(0, dot(V, R)), material_shininess) * material_ks;

		//specular_light = pow(max(dot(N, H), 0), material_shininess);
	}	

	// TODO: compute light

	// TODO: send color light output to fragment shader
	color = (ambient_light + atenuare * (max(diffuse_light + specular_light, 0))) * object_color;

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
