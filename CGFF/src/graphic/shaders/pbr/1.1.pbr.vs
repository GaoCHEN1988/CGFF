#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;

void main()
{
    TexCoords = aTexCoords;
    WorldPos = vec3(sys_ModelMatrix * vec4(aPos, 1.0));
    Normal = mat3(sys_ModelMatrix) * aNormal;   

    gl_Position =  sys_ProjectionMatrix * sys_ViewMatrix * vec4(WorldPos, 1.0);
}