#ifndef GLOBAL_H
#define GLOBAL_H

#include <glm/glm.hpp>

// glm::translate, glm::rotate, and glm::scale.
#include <glm/gtc/matrix_transform.hpp>

// glm::translate, glm::rotate, and glm::scale.
#include <glm/gtx/matrix_transform_2d.hpp>

// glm::to_string.
#include <glm/gtx/string_cast.hpp>

#include <glm/gtx/quaternion.hpp>


#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Core>
#include <QApplication>
#include <QKeyEvent>
#include <QTextStream>

#include <vector>
#include <array>
#include <memory>

#include <iostream>
#include <math.h>
#define M_PI 3.141592

using namespace std;

extern glm::vec4 _red;
extern glm::vec4 _green;
extern glm::vec4 _yellow;
extern glm::vec4 _blue;
extern glm::vec4 _black;
extern glm::vec4 _white;
extern glm::vec4 _grey;
extern glm::vec4 _purple;
extern glm::vec4 _normal;

inline void pl(string s)
{
    cout << s << endl;
}

inline void pl(float f, string s = "")
{
    cout << s << ": " << f << endl;
}

inline void pl(glm::vec2 v, string s = "")
{
    cout << s << ": " << v.x << ", " << v.y << endl;
}

inline void pl(glm::vec3 v, string s = "")
{
    cout << s << ": " << glm::to_string(v) << endl;
}

inline void pl(glm::vec4 v, string s = "")
{
    cout << s << ": " << glm::to_string(v) << endl;
}

inline void pl(glm::mat3 m, string s = "")
{
    cout << s << ": " << glm::to_string(m) << endl;
}

inline void pl(glm::mat4 m, string s = "")
{
    cout << s << ": " << glm::to_string(m) << endl;
}

inline std::string fromFile(const char *fileName)
{
    QString text;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        text = in.readAll();
        text.append('\0');
    }
    return text.toStdString();
}


#endif // GLOBAL_H
