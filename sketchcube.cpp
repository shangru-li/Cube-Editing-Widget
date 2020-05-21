#include "sketchcube.h"

const float SIZE2 = 0.5f;
glm::vec4 SketchCube::p0{-SIZE2, -SIZE2, -SIZE2, 1};
glm::vec4 SketchCube::p1{-SIZE2, -SIZE2, SIZE2, 1};
glm::vec4 SketchCube::p2{-SIZE2, SIZE2, -SIZE2, 1};
glm::vec4 SketchCube::p3{-SIZE2, SIZE2, SIZE2, 1};
glm::vec4 SketchCube::p4{SIZE2, -SIZE2, -SIZE2, 1};
glm::vec4 SketchCube::p5{SIZE2, -SIZE2, SIZE2, 1};
glm::vec4 SketchCube::p6{SIZE2, SIZE2, -SIZE2, 1};
glm::vec4 SketchCube::p7{SIZE2, SIZE2, SIZE2, 1};

SketchCube::SketchCube(CubeContext *context): Drawable(context)
{

}

void SketchCube::createGeometry()
{
    vertexBuffer.clear();
    indexBuffer.clear();
    glm::vec4 n(0, 0, 1, 0);
    glm::mat4 transform = glm::translate(glm::mat4(1.f), position);
    std::vector<glm::vec4> v{transform * p0, _red, n,
                transform * p1, _blue, n,
                transform * p2, _yellow, n,
                transform * p3, _white, n,
                transform * p4, _black, n,
                transform * p5, _grey, n,
                transform * p6, _purple, n,
                transform * p7, _green, n};
    std::vector<int> ib{2, 3, 2, 6, 7, 3, 7, 6,
                        1, 5, 1, 3, 7, 5, 7, 3,
                        2, 0, 2, 6, 4, 0, 4, 6,
                        2, 0, 2, 3, 1, 0, 1, 3,
                        5, 4, 5, 7, 6, 4, 6, 7,
                        0, 4, 5, 4, 0, 1, 5, 1};
    for (int &j : ib) j += vertexBuffer.size() / 3;
    vertexBuffer.insert(vertexBuffer.end(), v.begin(), v.end());
    indexBuffer.insert(indexBuffer.end(), ib.begin(), ib.end());
}
