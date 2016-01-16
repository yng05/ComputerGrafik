#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location=0) in vec3 in_Position;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
    vec4 p = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f);
    gl_Position = p;
}
