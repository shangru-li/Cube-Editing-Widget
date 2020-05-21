#ifndef CUBECONTEXT_H
#define CUBECONTEXT_H
#include <QTimer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "global.h"
#include "camera.h"
#include "shaderprogram.h"
#include "cubematrix.h"
#include "sketchcube.h"
#include <fstream>
#include <sstream>

class CubeContext: public QOpenGLWidget, public QOpenGLFunctions_3_2_Core
{
    Q_OBJECT

public:
    CubeContext(QWidget *parent);
    ~CubeContext() {}

    // update rendering
    void initializeGL();
    void paintGL();
    std::unique_ptr<Camera> camera;

    // interaction
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    glm::vec3 sketchPosition;
    glm::vec4 currentColor;

    // geometry
    CubeMatrix cubeMatrix;
    SketchCube sketchCube;

private:
    QTimer timer; // controls frame rate
    GLuint vao; // handle for vao
    const float fps;
    glm::mat4 offsetTx;
    std::array<bool, 256> keyboardStates;
    ShaderProgram shaderProgram, shaderProgramFlat;

private slots:
    void timerUpdate(); // called every frame

public slots:
    void updateRed(int x);
    void updateGreen(int x);
    void updateBlue(int x);

    void save();
    void load();
};
#endif // CUBECONTEXT_H
