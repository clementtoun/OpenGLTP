//
// Created by clement on 29/03/2022.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Material.h"

unsigned int loadTexture(char const * path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else {
            std::cout << "Texture failed format " << path << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (int) format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

Material::Material(glm::vec3 color, float roughness, float metallic) : m_color(color), m_roughness(roughness), m_metallic(metallic),
m_HAS_COLOR_TEXTURE(false), m_color_Texture(0), m_HAS_ROUGHNESS_TEXTURE(false), m_roughness_texture(0),
m_HAS_METALLIC_TEXTURE(false), m_metallic_texture(0) {}

void Material::setColor(const glm::vec3 &Color) {
    m_color = Color;
}

void Material::setRoughness(float Roughness) {
    m_roughness = Roughness;
}

void Material::setMetallic(float Metallic) {
    m_metallic = Metallic;
}

const glm::vec3 &Material::getColor() const {
    return m_color;
}

float Material::getRoughness() const {
    return m_roughness;
}

float Material::getMetallic() const {
    return m_metallic;
}

unsigned int Material::getColorTexture() const {
    return m_color_Texture;
}

void Material::setColorTexture(unsigned int ColorTexture) {
    m_HAS_COLOR_TEXTURE = true;
    m_color_Texture = ColorTexture;
}

unsigned int Material::getRoughnessTexture() const {
    return m_roughness_texture;
}

void Material::setRoughnessTexture(unsigned int RoughnessTexture) {
    m_HAS_ROUGHNESS_TEXTURE = true;
    m_roughness_texture = RoughnessTexture;
}

unsigned int Material::getMetallicTexture() const {
    return m_metallic_texture;
}

void Material::setMetallicTexture(unsigned int MetallicTexture) {
    m_HAS_METALLIC_TEXTURE = true;
    m_metallic_texture = MetallicTexture;
}

bool Material::isHasColorTexture() const {
    return m_HAS_COLOR_TEXTURE;
}

bool Material::isHasRoughnessTexture() const {
    return m_HAS_ROUGHNESS_TEXTURE;
}

bool Material::isHasMetallicTexture() const {
    return m_HAS_METALLIC_TEXTURE;
}

Material::~Material() {
    if(m_HAS_COLOR_TEXTURE)
        glDeleteTextures(1, &m_color_Texture);
    if(m_HAS_ROUGHNESS_TEXTURE)
        glDeleteTextures(1, &m_roughness_texture);
    if(m_HAS_METALLIC_TEXTURE)
        glDeleteTextures(1, &m_metallic_texture);
}
