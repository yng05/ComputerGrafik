#version 150

in vec4 pass_Position;
in  vec4 pass_Normal;
in vec3 pass_Color;

out vec4 out_Color;

void main(void)
{



    out_Color = vec4( pass_Color, 1.0f);
}
