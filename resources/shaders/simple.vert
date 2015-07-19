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
	vec4 vertexPos = vec4(in_Position, 1.0);
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vertexPos;

	// passed_normal = normalize(NormalMatrix * vec4(in_Normal, 0.0));
}
