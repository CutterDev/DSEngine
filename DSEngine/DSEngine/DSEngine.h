#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gameobject.h"
#include "GameCamera.h"
#include <iostream>

#include "Shader.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "BasicCubeNode.h"
#include "DSRenderer.h"
#include "Sprite.h"
#include "DSCore.h"
#include "SpriteComponent.h"
#include "EntityManager.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow* window);

class DSEngine
{
private:
    // settings
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

    DSRenderer m_Renderer;
    EntityManager m_EntityManager;
public:
    void Run();

private:
    void Tick();
};

