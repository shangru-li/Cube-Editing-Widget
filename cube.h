#ifndef CUBE_H
#define CUBE_H
#include "global.h"
class Cube
{
public:
    Cube(glm::mat4 transform);
    glm::mat4 transform;
};

#endif // CUBE_H
