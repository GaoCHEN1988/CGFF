#version 440 core

layout(location = 0) out vec4 color;

uniform samplerCube u_EnvironmentMap;

in vec3 TexCoords;

void main()
{
	color = texture(u_EnvironmentMap, TexCoords);
};