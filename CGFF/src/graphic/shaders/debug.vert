#version 440

layout(location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;

out DATA
{
	vec4 fragPosition;
	vec4 color;
} vs_out;

void main()
{
	vs_out.fragPosition = sys_ModelMatrix * vec4(position, 1.0);
	vs_out.color = color;

	gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * sys_ModelMatrix * vec4(position, 1.0);

};