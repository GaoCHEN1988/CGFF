#version 440

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec3 normal;
	vec2 uv;
	vec3 color;
} fs_in;

uniform vec4 u_Color;
uniform vec3 u_LightPosition;
uniform float u_LightAttenuation;
uniform vec4 u_LightColor;

void main()
{
    vec3 light = u_LightPosition - vec3(fs_in.position);
	float face = dot(normalize(light), normalize(fs_in.normal));
	float intensity = (u_LightAttenuation / length(light)) * max(face, 0.0);
	intensity = max(intensity, 0.1);
	color = vec4(fs_in.color * intensity, 1.0);
};
