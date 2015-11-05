#version 150

in float pass_T;
out vec4 out_Color;


void main(void)
{
    out_Color = vec4(vec3(pass_T), 0.5f);
}
