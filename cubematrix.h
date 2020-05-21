#ifndef CUBEMATRIX_H
#define CUBEMATRIX_H

#include "drawable.h"

#define SIZE 0.5f
class CubeMatrix: public Drawable
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

    CubeMatrix(CubeContext *context);
    void createGeometry();

private:
    void addColoredCube(glm::vec4 color);
};

#endif // CUBEMATRIX_H
