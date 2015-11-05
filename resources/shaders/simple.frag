#version 150

in vec4 pass_Position;
in vec4 pass_Normal;
in vec4 pass_LightDirection;
in vec4 pass_EyeDirection;
in vec3 pass_Color;
in float pass_Shininess;
in float pass_Ambient;
in float pass_Specular;
in float pass_Diffuse;

in float pass_EmitsLight;

in float pass_DiscreteSteps;
in float pass_UseCellShading;

out vec4 out_Color;

void main(void)
{
    float diffuse;
    if (pass_EmitsLight == 1.0f)
    {
        diffuse = 1.0f;
    }
    else
    {
        diffuse = dot(pass_Normal, pass_LightDirection);
    }

    float specular;
    if (pass_EmitsLight == 1.0f) {
        specular = 0.0f;
    }
    else
    {
        vec3 h = normalize(pass_LightDirection.xyz + pass_EyeDirection.xyz);
        float alpha = max(dot(h, pass_Normal.xyz), 0.0f);
        specular = pow(alpha, pass_Shininess * 4.0f);
    }

    vec3 diffuseLight = vec3(0.0f, 0.0f, 0.0f);
    if (pass_Diffuse == 1.0f)
    {
        diffuseLight = diffuse * pass_Color;
    }

    vec3 specularLight = vec3(0.0f, 0.0f, 0.0f);
    if (pass_Specular == 1.0f)
    {
        specularLight = 0.3f * specular * pass_Color;
    }

    vec3 ambientLight = vec3(0.0f, 0.0f, 0.0f);
    if (pass_Ambient == 1.0f)
    {
        ambientLight = 0.1f * pass_Color;
    }

    vec3 totalLight = ambientLight + diffuseLight + specularLight;

    // use cell shading
    if (pass_UseCellShading == 1.0f) {
        float l = length(totalLight);
        l = ceil(5.0f * pow(l, 0.5f)) / 5.0f;
        totalLight = normalize(totalLight) * l;

        float toonThreshold = dot(pass_Normal.xyz, pass_EyeDirection.xyz);
        if (toonThreshold > 0.0f && toonThreshold < 0.4f)
        {
            totalLight = vec3(1.0f, 0.0f, 0.0f);
        }
    }

    out_Color = vec4( totalLight, 1.0f);
}
