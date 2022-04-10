//
// Created by clement on 07/03/2022.
//
#ifndef OPENGLTP_MATERIAL_H
#define OPENGLTP_MATERIAL_H

#include "opengl_stuff.h"

#define DEFAULT_COLOR glm::vec3(1.0f,1.0f,1.0f)

unsigned int loadTexture(char const * path);

class Material {
public:
    Material(glm::vec3 color, float roughness, float metallic);
    ~Material();
    void setColor(const glm::vec3 &Color);
    void setRoughness(float Roughness);
    void setMetallic(float Metallic);
    const glm::vec3 &getColor() const;
    float getRoughness() const;
    float getMetallic() const;
    unsigned int getColorTexture() const;
    void setColorTexture(unsigned int ColorTexture);
    unsigned int getRoughnessTexture() const;
    void setRoughnessTexture(unsigned int RoughnessTexture);
    unsigned int getMetallicTexture() const;
    void setMetallicTexture(unsigned int MetallicTexture);
    bool isHasColorTexture() const;
    bool isHasRoughnessTexture() const;
    bool isHasMetallicTexture() const;
private:
    glm::vec3 m_color;
    float m_roughness;
    float m_metallic;
    bool m_HAS_COLOR_TEXTURE;
    unsigned int m_color_Texture;
    bool m_HAS_ROUGHNESS_TEXTURE;
    unsigned int m_roughness_texture;
    bool m_HAS_METALLIC_TEXTURE;
    unsigned int m_metallic_texture;

};

const Material Default_material(DEFAULT_COLOR, 0.5f, 0.5f);

const Material metal(DEFAULT_COLOR, 0.4f, 1.0f);

const Material smooth(DEFAULT_COLOR, 0.15f, 0.0f);

const Material rought(DEFAULT_COLOR, 1.0f, 0.0f);

const Material cool(DEFAULT_COLOR, 0.66f, 1.0f);

#endif //OPENGLTP_MATERIAL_H
