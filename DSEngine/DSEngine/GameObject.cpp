#include "gameobject.h"

void GameObject::Initialize(float vertices[], int verticesSize)
{
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
    Model = glm::mat4(1.0f);
    Model = glm::rotate(Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //
    // View
    View = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));

    Projection;
    Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void GameObject::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void GameObject::Delete()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}