#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <global.h>

class CubeContext;

class Drawable
{
public:
    Drawable(CubeContext *context);

    // fill geometry to vb and ib
    virtual void createGeometry() = 0;

    virtual glm::mat4 getModel();
    virtual int drawMode() { return GL_TRIANGLES; }

    void create();
    void destroy();
    void update();

    std::vector<int> indexBuffer;
    std::vector<glm::vec4> vertexBuffer;

    // for shader program
    GLuint hIndexBuffer, hVertexBuffer;
    int indexCount; // for drawing in shader program

protected:
    CubeContext *context;

private:
    bool hasGeneratedBuffer;
};

#endif // DRAWABLE_H
