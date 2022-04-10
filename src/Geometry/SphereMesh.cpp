//
// Created by clement on 27/03/2022.
//

#include "SphereMesh.h"

UVSphere::UVSphere(uint32_t meridians, uint32_t parallels) {
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    m_material = Default_material;
    m_type = TRIANGLE_MESH;
    using namespace glm;

    Vertex vert{};
    vert.vertices = vec3(0.0f, 1.0f, 0.0f);
    vert.Normal = vec3(0.0f,1.0f,0.0f);
    vert.TexCoords = vec2(0.0f,0.0f);
    m_vertices.emplace_back(vert);
    for (uint32_t j = 0; j < parallels - 1; ++j)
    {
        float polar = M_PI * float(j+1) / float(parallels);
        float sp = std::sin(polar);
        float cp = std::cos(polar);
        for (uint32_t i = 0; i < meridians; ++i)
        {
            float azimuth = 2.0 * M_PI * float(i) / float(meridians);
            float sa = std::sin(azimuth);
            float ca = std::cos(azimuth);
            float x = sp * ca;
            float y = cp;
            float z = sp * sa;
            if(i == 0){
                vert.TexCoords = vec2(1.0f, float(j+1) / float(parallels));
                vert.vertices = vec3(x, y, z);
                vert.Normal = vec3(0.0f,0.0f,0.0f);
                m_vertices.emplace_back(vert);
            }
            vert.TexCoords = vec2(float(i) / (float) meridians, float(j+1) / float(parallels));
            vert.vertices = vec3(x, y, z);
            vert.Normal = vec3(0.0f,0.0f,0.0f);
            m_vertices.emplace_back(vert);
        }
    }
    vert.vertices = vec3(0.0f, -1.0f, 0.0f);
    vert.Normal = vec3(0.0f,-1.0f,0.0f);
    vert.TexCoords = vec2(1.0f,1.0f);
    m_vertices.emplace_back(vert);

    meridians = meridians+1;

    for (uint32_t i = 0; i < meridians; ++i)
    {
        uint32_t const a = i + 1;
        uint32_t const b = (i + 1) % meridians + 1;
        addTriangle(0, b, a);
    }

    for (uint32_t j = 0; j < parallels - 2; ++j)
    {
        uint32_t aStart = j * meridians + 1;
        uint32_t bStart = (j + 1) * meridians + 1;
        for (uint32_t i = 0; i < meridians; ++i)
        {
            const uint32_t a = aStart + i;
            const uint32_t a1 = aStart + (i + 1) % meridians;
            const uint32_t b = bStart + i;
            const uint32_t b1 = bStart + (i + 1) % meridians;
            addQuad(a, a1, b1, b);
        }
    }

    for (uint32_t i = 0; i < meridians; ++i)
    {
        uint32_t const a = i + meridians * (parallels - 2) + 1;
        uint32_t const b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
        addTriangle(m_vertices.size() - 1, a, b);
    }

    computeNormal(1);
    setupMesh();
}

Icosahedron::Icosahedron(const unsigned int n_subdiv) {
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    m_material = Default_material;
    m_type = TRIANGLE_MESH;
    using namespace glm;

    const double t = (1.0 + std::sqrt(5.0)) / 2.0;

    // Vertices
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(-1.0,  t, 0.0)), glm::vec3(0.0f), glm::vec2(0.0f,0.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3( 1.0,  t, 0.0)), glm::vec3(0.0f), glm::vec2(0.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(-1.0, -t, 0.0)), glm::vec3(0.0f), glm::vec2(1.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3( 1.0, -t, 0.0)), glm::vec3(0.0f), glm::vec2(0.0f,0.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(0.0, -1.0,  t)), glm::vec3(0.0f), glm::vec2(0.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(0.0,  1.0,  t)), glm::vec3(0.0f), glm::vec2(1.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(0.0, -1.0, -t)), glm::vec3(0.0f), glm::vec2(0.0f,0.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(0.0,  1.0, -t)), glm::vec3(0.0f), glm::vec2(0.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3( t, 0.0, -1.0)), glm::vec3(0.0f), glm::vec2(1.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3( t, 0.0,  1.0)), glm::vec3(0.0f), glm::vec2(0.0f,0.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(-t, 0.0, -1.0)), glm::vec3(0.0f), glm::vec2(0.0f,1.0f)});
    m_vertices.emplace_back(Vertex{normalize(glm::vec3(-t, 0.0,  1.0)), glm::vec3(0.0f), glm::vec2(1.0f,1.0f)});

    // Faces
    addTriangle(0, 11, 5);
    addTriangle(0, 5, 1);
    addTriangle(0, 1, 7);
    addTriangle(0, 7, 10);
    addTriangle(0, 10, 11);
    addTriangle(1, 5, 9);
    addTriangle(5, 11, 4);
    addTriangle(11, 10, 2);
    addTriangle(10, 7, 6);
    addTriangle(7, 1, 8);
    addTriangle(3, 9, 4);
    addTriangle(3, 4, 2);
    addTriangle(3, 2, 6);
    addTriangle(3, 6, 8);
    addTriangle(3, 8, 9);
    addTriangle(4, 9, 5);
    addTriangle(2, 4, 11);
    addTriangle(6, 2, 10);
    addTriangle(8, 6, 7);
    addTriangle(9, 8, 1);

    for(unsigned int i = 0; i < n_subdiv; i++){
        SubdivideMesh();
    }

    computeNormal(1);
    setupMesh();
}

void Icosahedron::SubdivideMesh() {

    std::vector<unsigned int> indices = m_indices;
    m_indices.clear();

    for (uint32_t i = 0; i < indices.size(); i+=3)
    {
        const uint32_t f0 = indices[i];
        const uint32_t f1 = indices[i + 1];
        const uint32_t f2 = indices[i + 2];

        const glm::vec3 v0 = m_vertices[f0].vertices;
        const glm::vec3 v1 = m_vertices[f1].vertices;
        const glm::vec3 v2 = m_vertices[f2].vertices;

        const glm::vec3 v3 = glm::normalize(glm::vec3(0.5) * (v0 + v1));
        const uint32_t f3 = m_vertices.size();
        m_vertices.emplace_back(Vertex{v3, glm::vec3(0.0f), glm::vec2(0.0f,0.0f)});
        const glm::vec3 v4 = glm::normalize(glm::vec3(0.5) * (v1 + v2));
        const uint32_t f4 = m_vertices.size();
        m_vertices.emplace_back(Vertex{v4, glm::vec3(0.0f), glm::vec2(0.0f,1.0f)});
        const glm::vec3 v5 = glm::normalize(glm::vec3(0.5) * (v2 + v0));
        const uint32_t f5 = m_vertices.size();
        m_vertices.emplace_back(Vertex{v5, glm::vec3(0.0f), glm::vec2(1.0f,1.0f)});

        addTriangle(f0, f3, f5);
        addTriangle(f3, f1, f4);
        addTriangle(f4, f2, f5);
        addTriangle(f3, f4, f5);
    }
}
