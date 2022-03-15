#ifndef SCENE_H
#define SCENE_H


#include <vector>

#include <QOpenGLFunctions_4_1_Core>
#include "opengl_stuff.h"
#include "Renderer.h"

/** Simple class for managing an OpenGL demo
 */
class OpenGLDemo : public QOpenGLFunctions_4_1_Core {

public:
    explicit OpenGLDemo(int width, int height);
    virtual ~OpenGLDemo();

    virtual void resize(int width, int height);
    virtual void draw();

    void mouseclick(int button, float xpos, float ypos);
    void mousemove(float xpos, float ypos);
    void mousewheel(float delta);
    void keyboardmove(int key, double time);
    bool keyboard(unsigned char k);


    void toggledrawmode();

protected:
    // Width and heigth of the viewport
    int _width;
    int _height;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

private:
    // Rendering mode (true is filled, false is wireframed
    bool _drawfill;
    Renderer *m_renderer;
};


#endif // SCENE_H
