#version 440
uniform sampler2D texture;
varying vec4 color;
varying vec2 uv;
void main()
{
  gl_FragColor = texture2D(texture, uv.st);
  //gl_FragColor = color;
}
