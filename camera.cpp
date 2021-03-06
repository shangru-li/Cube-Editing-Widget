#include "camera.h"

Camera::Camera(float aspectRatio, float fovy, glm::vec3 eye, glm::vec3 ref)
    : eye(eye), ref(ref), aspectRatio(aspectRatio), fovy(fovy)
{
    front = glm::normalize(ref - eye);
    right = glm::cross(front, glm::vec3(0, 1, 0));
    up = glm::cross(right, front);
}

glm::mat4 Camera::getViewProj()
{
    return glm::perspective(fovy, aspectRatio, 0.1f, 1000.f) * glm::lookAt(eye, eye + front, up);

    return glm::mat4{glm::vec4{-1, 0, 0, 0},
        glm::vec4{0, 1, 0, 0},
        glm::vec4{0, 0, 1, 0},
        glm::vec4{0, 0, 1, 1},
       } * glm::mat4{glm::vec4{0.6667, 0, 0, 0},
        glm::vec4{0, 1, 0, 0},
        glm::vec4{0, 0, 1.0001, 1},
        glm::vec4{0, 0, -0.10001, 0}
        };
}

void Camera::rotateSpherical(float deg, glm::vec3 axis)
{
    glm::mat3 rotation = glm::mat3(glm::rotate(glm::mat4(1.f), deg, axis));
    eye = ref - eye; // vector between ref and eye
    eye = rotation * eye; // rotate the vector
    front = glm::normalize(eye); // new front
    eye = ref - eye; // new eye position
    right = rotation * right;
    up = rotation * up;
}

void Camera::zoom(float length)
{
    eye = eye + front * length;
}

void Camera::pan(glm::vec3 direction)
{
    float speed = 0.2f;
    eye += direction * speed;
    ref += direction * speed;
}
