#version 440

layout(location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

out DATA
{
	vec4 fragPosition;
	vec4 color;
	vec3 normal;
} vs_out;

void main()
{
	//vs_out.color = color;
	vs_out.fragPosition = sys_ModelMatrix * position;
	vs_out.normal = mat3(transpose(inverse(sys_ModelMatrix))) * normal; 
	vs_out.color = color;

	gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * sys_ModelMatrix * position;

};