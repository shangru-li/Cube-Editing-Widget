#include "cubematrix.h"

glm::vec4 CubeMatrix::p0{-SIZE, -SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p1{-SIZE, -SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p2{-SIZE, SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p3{-SIZE, SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p4{SIZE, -SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p5{SIZE, -SIZE, SIZE, 1};
glm::vec4 CubeMatrix::p6{SIZE, SIZE, -SIZE, 1};
glm::vec4 CubeMatrix::p7{SIZE, SIZE, SIZE, 1};

CubeMatrix::CubeMatrix(CubeContext *context): Drawable(context)
{
    matrix = std::vector<CubeItem>(MAT_SIZE_X * MAT_SIZE_Y * MAT_SIZE_Z);
    for (CubeItem &item: matrix)
        for (int &i: item)
            i = 0;
}

void CubeMatrix::createGeometry()
{
    vertexBuffer.clear();
    indexBuffer.clear();

    for (int i = 0; i < matrix.size(); ++i)
    {
        if (!isEmptyCube(i))
        {
            glm::vec3 coords = getCoords(i);
            CubeItem item = matrix.at(i);
            glm::vec4 color(item.at(0) / 255.f, item.at(1) / 255.f, item.at(2) / 255.f, item.at(3));
            addColoredCube(glm::translate(glm::mat4(1.f), coords), color);
        }
    }
}


void CubeMatrix::addCube(glm::vec3 position, glm::vec4 color)
{
    std::array<int, 4> &item = matrix.at(getCoords(position));
    item.at(0) = color.r;
    item.at(1) = color.g;
    item.at(2) = color.b;
    item.at(3) = 1;
}

void CubeMatrix::deleteCube(glm::vec3 position)
{
    std::array<int, 4> &item = matrix.at(getCoords(position));
    item.at(3) = 0;
}

CubeItem &CubeMatrix::operator()(int x, int y, int z)
{
    return matrix.at(getCoords(glm::vec3(x, y, z)));
}

CubeItem &CubeMatrix::operator()(glm::vec3 position)
{
    return matrix.at(getCoords(position));
}

void CubeMatrix::addColoredCube(glm::mat4 transform, glm::vec4 color)
{
    glm::vec4 n(0, 0, 1, 0);
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
