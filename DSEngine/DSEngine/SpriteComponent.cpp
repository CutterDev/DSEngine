#include "SpriteComponent.h"
#include "Entity.h"

class Entity;

SpriteComponent::SpriteComponent(Entity* entity, glm::vec3 color) : IComponent(entity)
{
    m_Color = color;
}

void SpriteComponent::Start()
{

}

void SpriteComponent::Update()
{
    // prepare transformations
    m_Shader->Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * p_Entity->Size.x, 0.5f * p_Entity->Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(p_Entity->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * p_Entity->Size.x, -0.5f * p_Entity->Size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(p_Entity->Size, 1.0f)); // last scale

    m_Shader->SetMat4("model", model);

    // render textured quad
    m_Shader->SetVec3("spriteColor", m_Color);

    m_Sprite->Draw();
}

void SpriteComponent::End()
{

}

void SpriteComponent::AssignSprite(Sprite* sprite)
{
    m_Sprite = sprite;
}

void SpriteComponent::AssignShader(Shader* shader)
{
    m_Shader = shader;
}