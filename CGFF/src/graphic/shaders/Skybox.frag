#version 440 core

layout(location = 0) out vec4 color;

uniform samplerCube u_EnvironmentMap;

in vec3 TexCoords;

void main()
{
	//color = textureLod(u_EnvironmentMap, fs_in.position.xyz, 4.0f);
	color = texture(u_EnvironmentMap, TexCoords);
};