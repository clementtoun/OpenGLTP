//
// Created by clement on 05/02/2022.
//

#ifndef OPENGL_TP_SHADER_H
#define OPENGL_TP_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "opengl_stuff.h"

class Shader {
public:

    Shader();

    void createProgram(const char *vertexPath, const char *fragmentPath);
    void use();
    void deleteProg();

    GLuint get_ID();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setMat4(const std::string &name, glm::mat4 mat);
    void setVec3(const std::string &name, glm::vec3 value);
    void setVec4(const std::string &name, glm::vec4 value);

private:
    //program ID
    GLuint ID;
};


#endif //OPENGL_TP_SHADER_H
