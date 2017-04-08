#version 440 core
//uniform sampler2D texture;
uniform sampler2D textures[32];
in vec2 uv;
in float tid;
in vec4 color;

out vec4 out_color;

void main()
{
	vec4 texColor = color;

	if(tid>0.0)
	{
		int t = int(tid - 0.5);
		texColor = color*texture(textures[t], uv);
	}
	out_color = texColor;
	//gl_FragColor = color;
}
