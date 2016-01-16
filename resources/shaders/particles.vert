#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Velocity;
layout(location=2) in vec3 in_Color;
layout(location=3) in float in_Lifetime;
layout(location=4) in float in_Transparency;
layout(location=5) in float in_Corner;
layout(location=6) in float in_Size;
layout(location=7) in float in_Offset;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float Time;



out vec4 color;
out vec2 texCoord;
out float transparency;
out vec4 position;
out vec4 lightPosition;

float calc_time(float global_time)
{
    return mod(global_time + in_Offset, in_Lifetime) / in_Lifetime;
}

vec3 calc_position(float time)
{
    return in_Position + in_Velocity * time;
}

float calc_transparency(float time)
{
    return in_Transparency * (in_Lifetime-time) / in_Lifetime;
}

float calc_size(float time)
{
    return in_Size * (in_Lifetime-time) / in_Lifetime;
}

void main(void)
{
    
    float t = calc_time(Time);
    vec4 p = vec4(calc_position(t), 1.0f);
    p = ViewMatrix * ModelMatrix * p;

    float size = calc_size(t);

    if (in_Corner == 0)
    {
        p.xy += vec2(-1,-1) * size;
        texCoord = vec2(0,0);
    }
    else if (in_Corner == 1)
    {
        p.xy += vec2(-1, 1) * size;
        texCoord = vec2(0,1);
    }
    else if (in_Corner == 2)
    {
        p.xy += vec2(1, -1) * size;
        texCoord = vec2(1,0);
    }
    else if (in_Corner == 3)
    {
        p.xy += vec2(1,1) * size;
        texCoord = vec2(1,1);
    }

    color = vec4(in_Color, 1);

    transparency = calc_transparency(t);

    p = ProjectionMatrix * p;
    gl_Position =  p;

    position = ModelMatrix * p;
    lightPosition = ModelMatrix * vec4(vec3(0), 1);
}