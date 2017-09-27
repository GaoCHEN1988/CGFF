#version 440 core

layout(location = 0) in vec4 position;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * sys_ModelMatrix * position;
}