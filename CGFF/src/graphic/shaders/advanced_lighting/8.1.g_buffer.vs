#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 binormal;
layout (location = 4) in vec3 tangent;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;

void main()
{
    vec4 worldPos = sys_ModelMatrix * vec4(aPos, 1.0);
    FragPos = worldPos.xyz; 
    TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(sys_ModelMatrix)));
    Normal = normalMatrix * aNormal;

    gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * worldPos;
}