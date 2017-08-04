#version 440 core
//uniform sampler2D texture;
uniform sampler2D textures[32];
in vec2 uv;
in vec2 mask_uv;
in float tid;
in float mid;
in vec4 color;

out vec4 out_color;

void main()
{
	vec4 texColor = color;
	vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);

	if(tid > 0.0)
	{
		int t = int(tid - 0.5);
		texColor = color*texture(textures[t], uv);
	}

    if (mid > 0.0)
	{
		int m = int(mid - 0.5);
		maskColor = texture(textures[m], mask_uv);
	}

	out_color = texColor * maskColor;	
}
