#version 150
#extension GL_ARB_explicit_attrib_location : require

// vertex attributes of VAO
layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexCoord;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec2 Resolution;

out vec2 pass_TexCoord;
out vec4 sun_coord;

void main(void)
{
    sun_coord =  (ProjectionMatrix*ViewMatrix) *  vec4(vec3(0.0f), 1.0f);
    sun_coord.xy = (sun_coord.xy / sun_coord.z + vec2(1.0)) / 2;

    vec4 p = vec4(in_Position, 1.0f);
	gl_Position = p;
    pass_TexCoord = in_TexCoord;
}
