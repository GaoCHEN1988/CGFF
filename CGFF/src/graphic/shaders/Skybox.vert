#version 440 core

layout(location = 0) in vec4 position;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

uniform mat4 invViewProjMatrix;

out vec3 TexCoords;

void main()
{
	TexCoords = position.xyz;
    //vec4 pos = sys_ProjectionMatrix * sys_ViewMatrix * position;
    vec4 pos =  sys_ProjectionMatrix * position;
	gl_Position = pos.xyww;
};

