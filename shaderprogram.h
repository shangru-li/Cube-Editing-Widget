#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "global.h"
#include "drawable.h"

class CubeContext;
class ShaderProgram
{
public:
    ShaderProgram(CubeContext *context);

    void create(const char *vertexFile, const char *fragmentFile);
    void draw(Drawable &drawable);

    void setModelViewProj(glm::mat4 viewProj, glm::mat4 model = glm::mat4(1.f));
    void setCamPos(glm::vec4 camPos);

protected:
    CubeContext *context;

private:
    // handles to the shader variables
    int attrPosition, attrColor, attrNormal;
    int unifViewProj, unifModel, unifModelInvTr, unifCamPos;

    // handles to the shaders and the program
    GLuint hVertexShader, hFragmentShader, hProgram;

    inline void useMe();
};

#endif // SHADERPROGRAM_H
