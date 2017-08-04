#version 440 core
// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec2 in_mask_uv;
layout (location = 3) in float in_tid;
layout (location = 4) in float in_mid;
layout (location = 5) in vec4 v_color;

out vec2 uv;
out vec2 mask_uv;
out float tid;
out float mid;
out vec4 color;

uniform mat4 projMatrix = mat4(1.0);
uniform mat4 mvMatrix = mat4(1.0);

void main(){

	uv = in_uv;
	tid = in_tid;
    mid = in_mid;
	color = v_color;
    mask_uv = in_mask_uv;

	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
}

