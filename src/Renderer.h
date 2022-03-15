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
#include "camera.h"

class Renderer {

public:
    Renderer(Shader &shader, Shader &lineShader, int width, int height);
    ~Renderer();
    void resize(int width, int height);
    void Draw();
    void add_Drawable(Drawable *drawable);
    void add_Light(glm::vec4 light);
    void change_Camera();
    Camera * get_Camera();
    void toggleNormalmode();

protected:
    glm::vec4 m_lightVector = glm::vec4(-5.0,7.0,3.0,1.0);
private:
    std::vector<Drawable*> m_drawables;
    Shader m_shader;
    Shader m_lineShader;

    int m_width;
    int m_height;

    std::unique_ptr<Camera> m_camera;
    using cameraconstructor=std::function<Camera*(glm::vec3, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat)>;
    std::vector<cameraconstructor> m_cameraconstructors;
    unsigned int m_active_camera;

    bool m_normal_mode = 0;

};


#endif //UNTILTED1_RENDERER_H
