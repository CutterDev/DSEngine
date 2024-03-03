#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <string>
#include <memory>
#include "IComponent.h"

//class Entity
//{
//public:
//    glm::mat4 Transform;
//private:
//    std::string m_Name;
//    std::vector<std::shared_ptr<IComponent>> m_Components;
//public:
//    Entity(std::string name);
//    void AddComponent(std::shared_ptr<IComponent> component);
//    void RemoveComponent(IComponent component);
//    void UpdateComponents();
//
//};