#include "gameobject.h"

void GameObject::Update(GameCamera* camera)
{
    for (auto &node : GameNodes)
    {
        node->Update(camera, this);
    }
}

void GameObject::Rotate(float rotation, glm::vec3 axis)
{
    Transform = glm::rotate(Transform, glm::radians(rotation), axis);
}

void GameObject::Translate(glm::vec3 pos)
{
    Transform = glm::translate(Transform, pos);
}


void GameObject::Translate(float x, float y, float z)
{
    Transform = glm::translate(Transform, glm::vec3(x, y, z));
}

void GameObject::Scale(glm::vec3 scale)
{
    Transform = glm::scale(Transform, scale);
}

glm::mat4 GameObject::GetTransform()
{
    if (Parent != NULL)
    {
        return Parent->Transform * Transform;
    }
    else
    {
        return Transform;
    }
}

glm::vec3 GameObject::Position()
{
    glm::vec3 pos;
    if (Parent != NULL)
    {
        pos = (Parent->GetTransform() * Transform)[3];
    }
    else
    {
        pos = Transform[3];
    }

    return pos;
}

void GameObject::AddNode(GameNode* gameNode)
{
    GameNodes.push_back(gameNode);
}

GameObject::~GameObject()
{

}