#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_TexCoord;
layout(location=3) in vec3 in_Tangent;
layout(location=4) in vec3 in_Bitangent;
//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;
uniform vec3 LightPosition; // world coordinates

out vec4 pass_Normal;
out vec4 pass_LightDirection;
out vec4 pass_EyeDirection;
out vec2 pass_TexCoord;
out mat3 pass_TangentMatrix;


void main(void)
{

    vec4 p = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f);
    gl_Position = p;

    pass_Normal = vec4(normalize(vec3(NormalMatrix * vec4(in_Normal, 0.0f))), 0.0f);

    vec3 mat_normal = normalize(vec3(NormalMatrix * vec4(in_Normal, 0.0f)));
    vec3 mat_tangent = normalize(vec3(NormalMatrix * vec4(in_Tangent, 0.0f)));
    vec3 mat_bitangent = normalize(vec3(NormalMatrix * vec4(in_Bitangent, 0.0f)));

    pass_TangentMatrix = mat3(mat_tangent, mat_bitangent, mat_normal);

    vec4 worldPosition = ModelMatrix * vec4(in_Position, 1.0f);         // world coordinates
    vec4 lightDirection = vec4(LightPosition, 1.0f) - worldPosition;    // world coordinates
    pass_LightDirection = vec4(normalize(vec3(ViewMatrix * lightDirection)), 0.f);

    pass_EyeDirection = vec4(-normalize(vec3((ViewMatrix * ModelMatrix) * vec4(vec3(0.0f), 1.0f))), 0.0f);

    pass_TexCoord = in_TexCoord;

}
