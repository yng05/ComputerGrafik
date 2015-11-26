#version 150

uniform sampler2D ColorTex;
uniform sampler2D NormalTex;

uniform vec3 Color;
uniform vec3 LightPosition; // world coordinates
uniform int EmitsLight;
uniform float Shininess;
uniform float Ambient;
uniform float Specular;
uniform float Diffuse;
uniform float CellShading;

in vec4 pass_Normal;
in vec4 pass_LightDirection;
in vec4 pass_EyeDirection;
in vec2 pass_TexCoord;

in mat3 pass_TangentMatrix;

out vec4 out_Color;

void main(void)
{
    vec4 textureColor = texture(ColorTex, pass_TexCoord);

    vec3 detailNormal = texture(NormalTex, pass_TexCoord).rgb;
    detailNormal = 2.0f * (detailNormal - vec3(0.5f));

    vec4 normal = vec4(normalize(pass_TangentMatrix * detailNormal), 0.0f);

    // normal = pass_Normal;

    float diffuse;
    if (EmitsLight == 1.0f)
    {
        diffuse = 1.0f;
    }
    else
    {
        diffuse = max(0, dot(normal, pass_LightDirection));
    }

    float specular;
    if (EmitsLight == 1.0f) {
        specular = 0.0f;
    }
    else
    {
        vec3 h = normalize(pass_LightDirection.xyz + pass_EyeDirection.xyz);
        float alpha = max(dot(h, normal.xyz), 0.0f);
        specular = pow(alpha, Shininess * 4.0f);
    }

    vec3 diffuseLight = vec3(0.0f, 0.0f, 0.0f);
    if (Diffuse == 1.0f)
    {
        diffuseLight = diffuse * textureColor.rgb;
    }

    vec3 specularLight = vec3(0.0f, 0.0f, 0.0f);
    if (Specular == 1.0f)
    {
        specularLight = 0.3f * specular * vec3(1.0f);
    }

    vec3 ambientLight = vec3(0.0f, 0.0f, 0.0f);
    if (Ambient == 1.0f)
    {
        ambientLight = 0.1f * textureColor.rgb;
    }

    vec3 totalLight = ambientLight + diffuseLight + specularLight;

    // use cell shading
    if (CellShading == 1.0f) {
        float l = length(totalLight);
        l = ceil(5.0f * pow(l, 0.5f)) / 5.0f;
        totalLight = normalize(totalLight) * l;

        float toonThreshold = dot(normal.xyz, pass_EyeDirection.xyz);
        if (toonThreshold > 0.0f && toonThreshold < 0.4f)
        {
            totalLight = vec3(1.0f, 0.0f, 0.0f);
        }
    }

    


    // out_Color = vec4(pass_TexCoord, 0.0f, 1.0f);
    // out_Color = vec4 (color.rgb / 2, 1.0f);
    // out_Color = vec4( normal.rgb, 1.0f);
    out_Color = vec4(totalLight, 1.0f);

    // out_Color = vec4( texture(NormalTex, pass_TexCoord).rgb, 1.0f);

    //out_Color = vec4( 1.0f);
}
