#version 440 core

layout(location = 0) out vec4 color;

struct Light
{
	vec4 color;
	vec3 position;
	float p0;
	vec3 direction;
	float p1;
	vec3 lightVector;
	float intensity;
};

Light sys_Light;

uniform samplerCube u_EnvironmentMap;

in DATA
{
	vec4 position;
	vec2 uv;
} fs_in;

void main()
{
	color = textureLod(u_EnvironmentMap, fs_in.position.xyz, 4.0f);
};