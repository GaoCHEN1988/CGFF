#version 440
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec3 v_color;
varying vec4 color;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main(){

	color = vec4(v_color, 1.0);
	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);

}

