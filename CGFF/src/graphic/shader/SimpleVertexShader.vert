#version 440
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec2 in_uv;
attribute vec4 v_color;
varying vec4 color;
varying vec2 uv;
uniform mat4 projMatrix = mat4(1.0);
uniform mat4 mvMatrix = mat4(1.0);

void main(){

	color = v_color;
	uv = in_uv;
	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
	//gl_Position = mvMatrix * vec4(vertexPosition_modelspace, 1);

}

