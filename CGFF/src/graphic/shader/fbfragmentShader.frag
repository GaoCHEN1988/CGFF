#version 440

in vec2 uv;
out vec4 out_color;
uniform sampler2D tex;

void main()
{
    out_color = texture(tex, uv);
    //out_color = vec4(1.0, 1.0, 1.0, 1.0);
}
