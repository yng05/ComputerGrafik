#version 150

in vec2 texCoord;
in vec4 color;
in float transparency;
out vec4 out_Color;

void main(void)
{
    float d = length(texCoord - vec2(0.5));

    float t;
    if (d < 0.5)
    {
        t = exp(-1/(0.5-d)) / exp(0);
    }
    else
    {
        t = 0;
    }
    out_Color = color * vec4(vec3(1), t * transparency);
}