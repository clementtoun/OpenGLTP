#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

struct Light {
    vec4 vec;
    vec3 color;
};
#define NB_LIGHT 3
uniform Light lights[NB_LIGHT];

struct Material {
//shared metal/dielectric
    vec3 color;
    float roughness;
    float metallic;
    bool has_color_texture;
    sampler2D colorTexture;
    bool has_roughness_texture;
    sampler2D roughnessTexture;
    bool has_metallic_texture;
    sampler2D metallicTexture;
};
uniform Material material;

uniform vec3 eyePos;

uniform bool normalmode;
uniform bool Texcoordmode;

const float M_PI = 3.141592653589793;

float Heaviside(float x){
    return (x > 0.f) ? 1.0f : 0.0f;
}

float D(float alpha, float NdotH){
    float alpha2 = alpha*alpha;
    float D_tmp = (NdotH*NdotH) * (alpha2 - 1) + 1;
    return alpha2 * Heaviside(NdotH) / ( M_PI * (D_tmp*D_tmp) );
}

float G(float alpha, float NdotL, float HdotL, float NdotV, float HdotV) {
    float alpha2 = alpha*alpha;
    float G1 = 2 * abs(NdotL) * Heaviside(HdotL) / (abs(NdotL) + sqrt(alpha2 + (1 - alpha2) * (NdotL*NdotL)));
    float G2 = 2 * abs(NdotV) * Heaviside(HdotV) / (abs(NdotV) + sqrt(alpha2 + (1 - alpha2) * (NdotV*NdotV)));
    return G1 * G2;
}

vec3 gltf2_color(float NdotH, float NdotL, float NdotV, float HdotL, float HdotV, vec3 colorTexture, float roughness, float metallic){
    const vec3 dielectricSpecular = vec3(0.04, 0.04, 0.04);
    const vec3 black = vec3(0.f, 0.f, 0.f);

    vec3 c_diff = mix(colorTexture, black, metallic);
    vec3 f0 = mix(dielectricSpecular, colorTexture, metallic);
    float alpha = roughness*roughness;

    vec3 F = f0 + (1 - f0) * pow(clamp(1 - abs(HdotV), 0.001f, 1.0f), 5);
    vec3 f_diffuse = (1 - F) * (1 / M_PI) * c_diff;
    vec3 f_specular = F * D(alpha, NdotH) * G(alpha, NdotL, HdotL, NdotV, HdotV) / (4 * abs(NdotV) * abs(NdotL));

    return f_diffuse + f_specular;
}

void main()
{
    vec3 frag_color = vec3(0, 0, 0);
    if(normalmode) {
        frag_color = Normal*0.5f + 0.5f;
    }
    else if (Texcoordmode) {
        frag_color = vec3(TexCoords, 1.0f);
    }
    else {

        vec3 color_texture = material.has_color_texture ? vec3(texture(material.colorTexture, TexCoords)) : material.color;
        float roughness = material.has_roughness_texture ? texture(material.roughnessTexture, TexCoords).x : material.roughness;
        float metallic = material.has_metallic_texture ? texture(material.metallicTexture, TexCoords).x : material.metallic;

        vec3 V, L, N, H;
        V = normalize(eyePos - FragPos);
        N = gl_FrontFacing ? Normal : -Normal;

        float NdotV = clamp(dot(N,V), 0.001f, 1.0f);
        float NdotH;
        float NdotL;
        float HdotL;
        float HdotV;

        for(int i = 0; i < NB_LIGHT; i++){
            L = normalize(vec3(lights[i].vec.xyz) - FragPos);
            H = normalize(L + V);

            NdotH = dot(N,H);
            NdotL = clamp(dot(N,L), 0.001f, 1.0f);
            HdotL = dot(H,L);
            HdotV = dot(H,V);

            frag_color += NdotL * lights[i].color * gltf2_color(NdotH, NdotL, NdotV, HdotL, HdotV, color_texture, roughness, metallic);
        }
    }

    FragColor = vec4(frag_color, 1.0f);
}