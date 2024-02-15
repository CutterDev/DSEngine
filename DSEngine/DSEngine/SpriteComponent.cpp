#include "SpriteComponent.h"
#include "Entity.h"

class Entity;

SpriteComponent::SpriteComponent(Entity* entity, glm::vec3 color) : IComponent(entity)
{
    m_Color = color;

    glBindVertexArray(VAO);
}

void SpriteComponent::Start()
{

}

void SpriteComponent::Update()
{
    // prepare transformations
    m_Shader->Use();
    m_Shader->SetMat4("projection", MainCamera->Projection);
    m_Shader->SetMat4("view", MainCamera->View);

    m_Shader->SetMat4("model", GetModel());

    // render textured quad
    m_Shader->SetVec3("spriteColor", m_Color);
}

glm::mat4 SpriteComponent::GetModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(p_Entity->Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * p_Entity->Size.x, 0.5f * p_Entity->Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(p_Entity->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * p_Entity->Size.x, -0.5f * p_Entity->Size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(p_Entity->Size, 1.0f)); // last scale

    return model;
}

glm::mat4* SpriteComponent::GetModelData()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(p_Entity->Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * p_Entity->Size.x, 0.5f * p_Entity->Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(p_Entity->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * p_Entity->Size.x, -0.5f * p_Entity->Size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(p_Entity->Size, 1.0f)); // last scale

    return &model;
}

void SpriteComponent::End()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void SpriteComponent::AssignSprite(Sprite* sprite)
{

    m_Sprite = sprite;

    // Add the entity point to the sprite
    m_Sprite->AddInstance(this);

}

void SpriteComponent::AssignShader(Shader* shader)
{
    m_Shader = shader;
}