#version 150

in float distance;
out vec4 out_Color;

void main(void)
{
    out_Color = vec4(vec3(50.0f / distance), 1.0f);
}
