#version 440

layout (location = 0) out vec4 Frag;

in DATA
{
	vec4 fragPosition;
	vec4 color;
} fs_in;


uniform vec3 sys_CameraPosition;

void main()
{
    Frag = fs_in.color;
};
