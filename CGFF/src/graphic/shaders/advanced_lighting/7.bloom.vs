#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform mat4 sys_ModelMatrix;
uniform vec3 sys_CameraPosition;


void main()
{
    vs_out.FragPos = vec3(sys_ModelMatrix * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
        
    mat3 normalMatrix = transpose(inverse(mat3(sys_ModelMatrix)));
    vs_out.Normal = normalize(normalMatrix * aNormal);
    
    gl_Position = sys_ProjectionMatrix * sys_ViewMatrix * sys_ModelMatrix * vec4(aPos, 1.0);
}