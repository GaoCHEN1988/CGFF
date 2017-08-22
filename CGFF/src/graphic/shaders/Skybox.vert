#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

uniform mat4 invViewProjMatrix;

out DATA
{
	vec4 position;
	vec2 uv;
} vs_out;

void main()
{
	vec4 pos = position;
	pos.z = 1.0f;
	gl_Position = pos;
	vs_out.position = invViewProjMatrix * pos;
	vs_out.uv = uv;
};

