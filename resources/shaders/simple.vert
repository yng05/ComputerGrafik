#version 330

layout(location=0) in vec3 in_Position;
// layout(location=1) in vec3 in_Normal;
// out vec4 passed_normal;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
// uniform mat4 NormalMatrix;


void main(void)
{
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);
}
