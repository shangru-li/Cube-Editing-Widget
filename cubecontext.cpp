#include "cubecontext.h"

CubeContext::CubeContext(QWidget *parent)
    : QOpenGLWidget(parent), fps(60.f),
      shaderProgram(this), shaderProgramFlat(this),
      cubeMatrix(this)
{
    // when it's time to update a frame
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

    // update every 16 ms
    timer.start(glm::round(1000 / fps));

    for (bool &state : keyboardStates) state = false;
}

void CubeContext::initializeGL()
{
    // initialize
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glPointSize(5);
    glClearColor(1, 1, 1, 1);
    setFocus();

    shaderProgram.create(":/resources/basic.vert.glsl", ":/resources/basic.frag.glsl");
    shaderProgramFlat.create(":/resources/flat.vert.glsl", ":/resources/flat.frag.glsl");
    camera = std::make_unique<Camera>((float)width() / height(), 90.f, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));
}

void CubeContext::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cubeMatrix.update();
    shaderProgram.setCamPos(glm::vec4(camera->eye, 1));
    shaderProgram.setModelViewProj(camera->getViewProj());
    shaderProgram.draw(cubeMatrix);
}

void CubeContext::keyPressEvent(QKeyEvent *e)
{
    // from a to z
    if (e->key() >= 0x30 && e->key() <= 0x5a)
        keyboardStates[e->key()] = true;
}

void CubeContext::keyReleaseEvent(QKeyEvent *e)
{
    // from a to z
    if (e->key() >= 0x30 && e->key() <= 0x5a)
        keyboardStates[e->key()] = false;
}

void CubeContext::timerUpdate()
{
    float roundsPerSecond = 0.25, rotateDegree = 360 * roundsPerSecond / fps, zoomLength = 0.1;
    if (keyboardStates['A']) camera->rotateSpherical(rotateDegree, camera->up);
    if (keyboardStates['D']) camera->rotateSpherical(-rotateDegree, camera->up);
    if (keyboardStates['W']) camera->rotateSpherical(rotateDegree, camera->right);
    if (keyboardStates['S']) camera->rotateSpherical(-rotateDegree, camera->right);
    if (keyboardStates['Q']) camera->zoom(-zoomLength);
    if (keyboardStates['E']) camera->zoom(zoomLength);
    if (keyboardStates['H']) camera->pan(camera->up);
    if (keyboardStates['N']) camera->pan(-camera->up);
    if (keyboardStates['B']) camera->pan(-camera->right);
    if (keyboardStates['M']) camera->pan(camera->right);

    update(); // update the widget
}
