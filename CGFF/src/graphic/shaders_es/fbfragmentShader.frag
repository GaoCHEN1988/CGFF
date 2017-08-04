#version 440
//uniform sampler2D texture;
uniform sampler2D textures[32];
varying vec2 uv;
varying vec2 mask_uv;
varying float tid;
varying float mid;
varying vec4 color;

void main()
{
	vec4 texColor = color;
    vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);

	if(tid>0.0)
	{
		int t = int(tid - 0.5);
		texColor = color*texture2D(textures[t], uv.st);
	}

    if (mid > 0.0)
	{
		int m = int(mid - 0.5);
		maskColor = texture2D(textures[m], mask_uv.st);
	}

	gl_FragColor = texColor * maskColor;
}
