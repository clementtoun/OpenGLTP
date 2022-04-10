#ifndef HelloSphereMaterial_H
#define HelloSphereMaterial_H


#include <vector>
#include "Renderer.h"
#include "opengldemo.h"

/** Simple class for managing an OpenGL demo
 */
class HelloSphereMaterial: public OpenGLDemo {

public:
    explicit HelloSphereMaterial(int width, int height);
    ~HelloSphereMaterial() override;

    void resize(int width, int height) override;
    virtual void draw();

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void mousewheel(float delta) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;

protected:
    // Width and heigth of the viewport
    int _width{};
    int _height{};

    // for mouse management
    int _button{0}; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

private:
    Renderer *m_renderer;
};


#endif // HelloSphereMaterial_H
