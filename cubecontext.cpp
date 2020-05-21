#include "cubecontext.h"

CubeContext::CubeContext(QWidget *parent)
    : QOpenGLWidget(parent), fps(60.f),
      shaderProgram(this), shaderProgramFlat(this),
      cubeMatrix(this), sketchCube(this),
      offsetTx(glm::translate(glm::mat4(1.f),
                              glm::vec3(-MAT_SIZE_X / 2.f,
                                        -MAT_SIZE_Y / 2.f,
                                        -MAT_SIZE_Z / 2.f)))
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
    glLineWidth(3);
    glClearColor(1, 1, 1, 1);

    shaderProgram.create(":/resources/basic.vert.glsl", ":/resources/basic.frag.glsl");
    shaderProgramFlat.create(":/resources/flat.vert.glsl", ":/resources/flat.frag.glsl");
    camera = std::make_unique<Camera>((float)width() / height(), 90.f, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));

    cubeMatrix.addCube(glm::vec3(7, 7, 7), _red);
    sketchCube.position = glm::vec3(7, 7, 7);
    setFocus();
}

void CubeContext::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cubeMatrix.update();
    sketchCube.update();
    shaderProgramFlat.setCamPos(glm::vec4(camera->eye, 1));
    shaderProgramFlat.setModelViewProj(camera->getViewProj(), offsetTx);
    shaderProgramFlat.draw(cubeMatrix);
    shaderProgramFlat.draw(sketchCube);
}

void CubeContext::keyPressEvent(QKeyEvent *e)
{
    setFocus();
    // from a to z
    if (e->key() >= 0x30 && e->key() <= 0x5a)
        keyboardStates[e->key()] = true;
    if (e->key() == 'L') if (CubeMatrix::isInBoundX(sketchCube.position.x - 1)) --sketchCube.position.x;
    if (e->key() == 'J') if (CubeMatrix::isInBoundX(sketchCube.position.x + 1)) ++sketchCube.position.x;
    if (e->key() == 'K') if (CubeMatrix::isInBoundY(sketchCube.position.y - 1)) --sketchCube.position.y;
    if (e->key() == 'I') if (CubeMatrix::isInBoundY(sketchCube.position.y + 1)) ++sketchCube.position.y;
    if (e->key() == 'O') if (CubeMatrix::isInBoundZ(sketchCube.position.z - 1)) --sketchCube.position.z;
    if (e->key() == 'U') if (CubeMatrix::isInBoundZ(sketchCube.position.z + 1)) ++sketchCube.position.z;
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
    if (keyboardStates['F']) cubeMatrix.addCube(sketchCube.position, currentColor);
    if (keyboardStates['G']) cubeMatrix.deleteCube(sketchCube.position);

    update(); // update the widget
}

void CubeContext::updateRed(int x)
{
    currentColor.r = x;
    setFocus();
}

void CubeContext::updateGreen(int x)
{
    currentColor.g = x;
    setFocus();
}

void CubeContext::updateBlue(int x)
{
    currentColor.b = x;
    setFocus();
}

void CubeContext::save()
{
    ofstream o("./saveFile.txt");
    for (int i = 0; i < cubeMatrix.matrix.size(); ++i)
    {
        const CubeItem &item = cubeMatrix.matrix.at(i);
        o << item.at(0) << " ";
        o << item.at(1) << " ";
        o << item.at(2) << " ";
        o << item.at(3) << "\n";
    }
    setFocus();
}

void CubeContext::load()
{
    ifstream in("./saveFile.txt");
    string s;
    for (int i = 0; i < cubeMatrix.matrix.size(); ++i)
    {
        getline(in, s);
        istringstream iss(s);
        for (int j = 0; j < 4; ++j)
        {
            int k;
            iss >> k;
            cubeMatrix.matrix.at(i).at(j) = k;
        }
    }
    setFocus();
}
