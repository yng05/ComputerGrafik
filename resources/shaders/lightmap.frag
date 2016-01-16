#version 150

uniform sampler2D ColorTex;
uniform sampler2D NormalTex;

uniform vec3 Color;
uniform vec3 LightPosition; // world coordinates
uniform bool EmitsLight;
uniform float Shininess;
uniform bool Ambient;
uniform bool Specular;
uniform bool Diffuse;
uniform bool CellShading;
uniform bool NoCellBorder;

in vec4 pass_Normal;
in vec4 pass_LightDirection;
in vec4 pass_EyeDirection;
in vec2 pass_TexCoord;

in mat3 pass_TangentMatrix;

out vec4 out_Color;

void main(void)
{
    vec4 textureColor = texture(ColorTex, pass_TexCoord);

    vec4 normal;

    if (!EmitsLight) 
    {
        vec3 detailNormal = texture(NormalTex, pass_TexCoord).rgb;
        detailNormal = 2.0f * (detailNormal - vec3(0.5f));

        normal = vec4(normalize(pass_TangentMatrix * detailNormal), 0.0f);
    } else {
        normal = pass_Normal;
    }

    float diffuse;
    if (EmitsLight)
    {
        diffuse = 1.0f;
    }
    else
    {
        diffuse = max(0, dot(normal, pass_LightDirection));
    }

    float specular;
    if (EmitsLight) {
        specular = 0.0f;
    }
    else
    {
        vec3 h = normalize(pass_LightDirection.xyz + pass_EyeDirection.xyz);
        float alpha = max(dot(h, normal.xyz), 0.0f);
        specular = pow(alpha, Shininess * 4.0f);
    }

    vec3 diffuseLight = vec3(0.0f, 0.0f, 0.0f);
    if (Diffuse)
    {
        diffuseLight = diffuse * textureColor.rgb;
    }

    vec3 specularLight = vec3(0.0f, 0.0f, 0.0f);
    if (Specular)
    {
        specularLight = 0.3f * specular * vec3(1.0f);
    }

    vec3 ambientLight = vec3(0.0f, 0.0f, 0.0f);
    if (Ambient)
    {
        ambientLight = 0.1f * textureColor.rgb;
    }

    vec3 totalLight = ambientLight + diffuseLight + specularLight;

    // use cell shading
    if (CellShading) {
        float l = length(totalLight);
        l = ceil(5.0f * pow(l, 0.5f)) / 5.0f;
        totalLight = normalize(totalLight) * l;

        float toonThreshold = dot(normal.xyz, pass_EyeDirection.xyz);
        if (toonThreshold > 0.0f && toonThreshold < 0.5f)
        {
            totalLight = float(NoCellBorder) * totalLight + (1.0f-float(NoCellBorder)) * vec3(0.0f, 0.0f, 0.0f);
        }
    }

    
    if (!EmitsLight) {
        totalLight = 0.0f * totalLight;
    }
    

    // out_Color = vec4(pass_TexCoord, 0.0f, 1.0f);
    // out_Color = vec4 (color.rgb / 2, 1.0f);
    // out_Color = vec4( normal.rgb, 1.0f);
    out_Color = vec4(totalLight, 1.0f);

    // out_Color = vec4( texture(NormalTex, pass_TexCoord).rgb, 1.0f);

    //out_Color = vec4( 1.0f);
}
