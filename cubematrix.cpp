#include "cubematrix.h"

glm::vec4 CubeMatrix::p0{-SIZE, -SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p1{-SIZE, -SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p2{-SIZE, SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p3{-SIZE, SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p4{SIZE, -SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p5{SIZE, -SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p6{SIZE, SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p7{SIZE, SIZE, SIZE, 1};

CubeMatrix::CubeMatrix(CubeContext *context): Drawable(context) {}

void CubeMatrix::createGeometry()
{
    vertexBuffer.clear();
    indexBuffer.clear();
    addColoredCube(_blue);
}

void CubeMatrix::addColoredCube(glm::vec4 color)
{
    glm::vec4 n(0, 0, 1, 0);
    glm::mat4 transform(1.f);
    std::vector<glm::vec4> v{transform * p0, color, n,
                transform * p1, color, n,
                transform * p2, color, n,
                transform * p3, color, n,
                transform * p4, color, n,
                transform * p5, color, n,
                transform * p6, color, n,
                transform * p7, color, n};
    std::vector<int> ib{2, 3, 6, 3, 6, 7,
                        1, 5, 3, 5, 7, 3,
                        0, 2, 6, 0, 6, 4,
                        0, 3, 2, 0, 1, 3,
                        4, 6, 7, 4, 7, 5,
                        1, 0, 4, 1, 4, 5};
    for (int &j : ib) j += vertexBuffer.size() / 3;
    vertexBuffer.insert(vertexBuffer.end(), v.begin(), v.end());
    indexBuffer.insert(indexBuffer.end(), ib.begin(), ib.end());
}
