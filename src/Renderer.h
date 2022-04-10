//
// Created by clement on 04/03/2022.
//

#ifndef UNTILTED1_RENDERER_H
#define UNTILTED1_RENDERER_H

#include <memory>
#include <functional>
#include <vector>
#include "opengl_stuff.h"
#include "Shader.h"
#include "Geometry/Drawable.h"
#include "Geometry/Mesh.h"
#include "Geometry/Light.h"
#include "camera.h"

class Renderer {

public:
    Renderer(Shader &shader, Shader &lineShader, Shader &lightShader, int width, int height);
    ~Renderer();
    void resize(int width, int height);
    void Draw();
    void add_Drawable(Drawable *drawable);
    void add_Light(Light *light);
    void change_Camera();
    Camera * get_Camera();
    void toggleNormalmode();
    void toggleTexcoordmode();

private:
    std::vector<Drawable*> m_drawables;
    std::vector<Light*> m_lights;
    Shader m_shader;
    Shader m_lineShader;
    Shader m_lightShader;

    int m_width;
    int m_height;

    std::unique_ptr<Camera> m_camera;
    using cameraconstructor=std::function<Camera*(glm::vec3, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat)>;
    std::vector<cameraconstructor> m_cameraconstructors;
    unsigned int m_active_camera;

    bool m_normal_mode = 0;
    bool m_Texcoord_mode = 0;

};


#endif //UNTILTED1_RENDERER_H
