#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;
uniform vec3 Color;

out vec4 pass_Normal;
out vec4 pass_Position;
out vec3 pass_Color;

void main(void)
{
    vec4 sun = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(vec3(0.0f), 1.0f);
    vec4 p = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f);

    vec4 world_coord = ModelMatrix * vec4(in_Position, 1.0f);
    pass_Position = -normalize(world_coord);

    pass_Color = Color;


	gl_Position = p;
	pass_Normal = vec4(normalize(vec3(NormalMatrix * vec4(in_Normal, 0.0f))), 0.0f);
}
