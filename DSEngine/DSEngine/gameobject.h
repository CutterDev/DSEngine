#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class GameObject 
{
private:
    unsigned int m_VAO, m_VBO, m_EBO;
public:
    glm::mat4 Model, View, Projection;

    void Initialize(float vertices[], int verticesSize);
    void Draw();
    void Delete();
};

#endif