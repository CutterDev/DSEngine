#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <memory>
#include <utility>
#include "Shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Game.h"

#include "DSRenderer.h"

#include "SpriteComponent.h"
#include "InputManager.h"
#include "InstrumentHandler.h"

#include "EntityManager.h";


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 500;
float currentWindowWidth = 0.0f;
float currentWindowHeight = 0.0f;
float lastFrameTime = 0.0f;
float zoom = 0.8f;
float targetWidth = SCR_WIDTH;
float targetHeight = SCR_HEIGHT;
float aspectRatio = targetWidth / targetHeight;

glm::vec2 currentMousePos = glm::vec2(0.0f);

float deltaTime = 0.0f;

std::unique_ptr<GameCamera> MainCamera;
// Modules
InputManager Input;
GLFWwindow* GameWindow = nullptr;
Game game;

void processInput(GLFWwindow* window);
void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void InitGL();
void Run();

int main()
{
    InitGL();

    game.Initialize(SCR_WIDTH, SCR_HEIGHT);

    Run();

    return EXIT_SUCCESS;
}

void Run()
{
    currentWindowWidth = SCR_WIDTH;
    currentWindowHeight = SCR_HEIGHT;
    glEnable(GL_DEPTH_TEST);

    //EntityManager EntityManager;
    float viewPortRatio = SCR_WIDTH / SCR_HEIGHT;


    double previousTime = glfwGetTime();
    int frameCount = 0;



    // render loop
    // -----------
    while (!glfwWindowShouldClose(GameWindow))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();

        // Measure speed
        frameCount++;
        // If a second has passed.
        if (currentFrameTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.
            std::cout << "==================" << std::endl;
            std::cout << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentFrameTime;
        }


        // input
        // -----
        processInput(GameWindow);


        // render
        // ------
        glClearColor(0.5f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
        game.Tick(deltaTime);
        //m_SpriteManager.Draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(GameWindow);
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    game.Shutdown();

    glfwDestroyWindow(GameWindow);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void InitGL()
{
    // glfw: initialize and configure
// ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GameWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (GameWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(GameWindow);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSetFramebufferSizeCallback(GameWindow, Framebuffer_Size_Callback);
    glfwSetCursorPosCallback(GameWindow, mouse_callback);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    game.PollInputs(window);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    game.PollMouseInput(xpos, ypos);
}

void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    currentWindowWidth = width;
    currentWindowHeight = height;
    game.FrameSizeChanged(width, height);
}