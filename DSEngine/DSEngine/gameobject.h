#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class GameObject 
{
private:
    unsigned int m_VAO, m_VBO;
    // Model is World Position
    // View Is Camera Positon;
    glm::mat4 m_Model;
    Shader* m_Shader;
public:
    static glm::mat4 Projection;
    static glm::mat4 View;
    GameObject(float vertices[], int verticesSize, Shader* shader);
    GameObject() {};
    ~GameObject();
    void Draw();
    void Rotate(float rotation, glm::vec3 axis);
    void Translate(glm::vec3 axis);
    void Translate(float x, float y, float z);


};


#endif