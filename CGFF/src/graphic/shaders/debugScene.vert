#version 440

layout(location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

out DATA
{
	vec4 color;
} vs_out;

void main()
{
	gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * sys_ModelMatrix * position;
	vs_out.color = color;
};