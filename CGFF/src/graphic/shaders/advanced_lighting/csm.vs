#version 440 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

void main()
{
    gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * sys_ModelMatrix * vec4(position, 1.0f);
    TexCoords = texCoords;
}