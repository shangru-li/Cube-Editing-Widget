#ifndef SKETCHCUBE_H
#define SKETCHCUBE_H
#include "drawable.h"
class SketchCube: public Drawable
{
public:
    static glm::vec4 p0;
    static glm::vec4 p1;
    static glm::vec4 p2;
    static glm::vec4 p3;
    static glm::vec4 p4;
    static glm::vec4 p5;
    static glm::vec4 p6;
    static glm::vec4 p7;

    SketchCube(CubeContext *context);
    glm::vec3 position;
    int drawMode() { return GL_LINES; }
    void createGeometry();
};

#endif // SKETCHCUBE_H
