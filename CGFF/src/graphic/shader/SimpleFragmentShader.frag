#version 440
//uniform sampler2D texture;
uniform sampler2D textures[32];
varying vec2 uv;
varying float tid;
varying vec4 color;

void main()
{
	vec4 texColor = color;

	if(tid>0.0)
	{
		int t = int(tid - 0.5);
		texColor = texture2D(textures[t], uv.st);
	}
	gl_FragColor = texColor;
	//gl_FragColor = color;
}
