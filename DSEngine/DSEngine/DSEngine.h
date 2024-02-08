#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gameobject.h"
#include "GameCamera.h"
#include <iostream>

#include "Shader.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "BasicCubeNode.h"
#include "DSRenderer.h"
#include "DSCore.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow* window);

class DSEngine
{
private:
    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    DSRenderer m_Renderer;
public:
    void Run();

private:
    void Tick();
};

