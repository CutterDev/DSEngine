#include "SpriteComponent.h"
#include "Entity.h"

class Entity;

SpriteComponent::SpriteComponent(Entity* entity, glm::vec3 color) : IComponent(entity)
{
    Color = color;
}

void SpriteComponent::Start()
{
    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(p_Entity->Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    Model = glm::translate(Model, glm::vec3(0.5f * p_Entity->Size.x, 0.5f * p_Entity->Size.y, 0.0f)); // move origin of rotation to center of quad
    Model = glm::rotate(Model, glm::radians(p_Entity->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    Model = glm::translate(Model, glm::vec3(-0.5f * p_Entity->Size.x, -0.5f * p_Entity->Size.y, 0.0f)); // move origin back

    Model = glm::scale(Model, glm::vec3(p_Entity->Size, 1.0f)); // last scale
}

void SpriteComponent::Update()
{
    // render textured quad
    //SpriteShader->SetVec3("spriteColor", Color);

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(0), 1000);
    glBindVertexArray(0);
}

void SpriteComponent::End()
{

}