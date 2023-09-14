#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Triangle
{
private:
    unsigned int m_VAO, m_VBO;
public:
    void Initialize(float vertices[], int size, int texture);
    void Draw();
    void Delete();
};


#endif