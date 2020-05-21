#ifndef CUBEMATRIX_H
#define CUBEMATRIX_H

#include "drawable.h"
#include "cube.h"
#define SIZE 0.5f
#define MAT_SIZE_X 15
#define MAT_SIZE_Y 15
#define MAT_SIZE_Z 15
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
    glm::mat4 getModel();

    void addCube(glm::vec3 position, glm::vec4 color);

    std::array<std::array<int, 4>, 200> matrix;
    std::array<int, 4> &operator() (int x, int y, int z);
    std::array<int, 4> &operator() (glm::vec3 position);
    bool isEmptyCube(int i) { return matrix.at(i).at(3) == 0; }

    inline static isBlack(glm::vec3 color) { return glm::vec4{color, 1} == _black; }
private:
    void addColoredCube(glm::mat4 transform, glm::vec4 color);
    inline static int getCoords(glm::vec3 v)
    {
        return v.z + v.y * MAT_SIZE_Z + v.x * MAT_SIZE_Y * MAT_SIZE_Z;
    }
    inline static glm::vec3 getCoords(int i)
    {
        return glm::vec3(i / (MAT_SIZE_Y * MAT_SIZE_Z),
                         i / MAT_SIZE_Z % MAT_SIZE_Y,
                         i % MAT_SIZE_Z);
    }
};

#endif // CUBEMATRIX_H
