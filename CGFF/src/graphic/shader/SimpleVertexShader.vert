#version 440
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec2 in_uv;
attribute float in_tid;
attribute vec4 v_color;
varying vec2 uv;
varying float tid;
varying vec4 color;

uniform mat4 projMatrix = mat4(1.0);
uniform mat4 mvMatrix = mat4(1.0);

void main(){

	uv = in_uv;
	tid = in_tid;
	color = v_color;

	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
	//gl_Position = mvMatrix * vec4(vertexPosition_modelspace, 1);

}

