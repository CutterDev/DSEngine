#include "Triangle.h"

void Triangle::Initialize(float vertices[], int size, int texture)
{
    // Bind Vertex Array
    glBindVertexArray(m_VAO);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Triangle::Draw()
{
    // Bind the Vertex Array
    glBindVertexArray(m_VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::Delete()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}