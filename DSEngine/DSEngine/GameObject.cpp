#include "gameobject.h"

GameObject::GameObject(float vertices[], int verticesSize, Shader* shader)
{
    m_Shader = shader;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // Transformation matrix
    //
    // Local Space
    m_Model = glm::mat4(1.0f);
}

void GameObject::Draw(GameCamera camera)
{
    m_Shader->Use();
    int modelLoc = glGetUniformLocation(m_Shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));

    int viewLoc = glGetUniformLocation(m_Shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.View));

    int projLoc = glGetUniformLocation(m_Shader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.Projection));

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Reset Model View
    m_Model = glm::mat4(1.0f);
}

void GameObject::Rotate(float rotation, glm::vec3 axis)
{
    m_Model = glm::rotate(m_Model, glm::radians(rotation), axis);
}

void GameObject::Translate(glm::vec3 pos)
{
    m_Model = glm::translate(m_Model, pos);
}

GameObject::~GameObject()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}