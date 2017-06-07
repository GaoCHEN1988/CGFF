#version 440

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec2 in_mask_uv;
layout (location = 3) in float in_tid;
layout (location = 4) in float in_mid;
layout (location = 5) in vec4 v_color;

out vec2 uv;

uniform mat4 projMatrix = mat4(1.0);

void main()
{
	uv = in_uv;
	gl_Position = projMatrix * position;
}