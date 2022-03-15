#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 color;
uniform vec4 lightVector;

uniform bool normalmode;

void main()
{
    if(normalmode) {
        FragColor = vec4(Normal*0.5f + 0.5f, 1.0f);
    }
    else {
        vec3 norm = normalize(Normal);
        if (lightVector.w == 0.0) {
            vec3 lightDir = normalize(vec3(-lightVector));
            float diff = max(dot(norm, lightDir), 0.0);
            FragColor = vec4(diff*color, 1.0f);// définit les quatre composantes du vecteur à 1.0
        }
        else {
            vec3 lightDir = normalize(lightVector.xyz - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 result = diff * color;
            FragColor = vec4(result, 1.0f);// définit les quatre composantes du vecteur à 1.0
        }
    }
}