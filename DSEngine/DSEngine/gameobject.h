#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameCamera.h"

#include "GameNode.h"
#include <vector>


class GameObject 
{
private:
    /// <summary>
    /// Game nodes Attached to the GameObject
    /// </summary>
    std::vector<GameNode*> GameNodes;
public:
    glm::mat4 Transform;
    GameObject* Parent = NULL;
    std::vector<GameObject*> Children;
    GameObject() { Transform = glm::mat4(1.0f); };
    ~GameObject();
    void Update(GameCamera* camera);
    void Rotate(float rotation, glm::vec3 axis);
    void Translate(glm::vec3 axis);
    void Translate(float x, float y, float z);
    void Scale(glm::vec3 scale);
    glm::vec3 Position();
    void AddNode(GameNode* gameNode);
    glm::mat4 GetTransform();
};

class Light : public GameObject {
    Light(float vertices[], int verticesSize, Shader* shader);
};