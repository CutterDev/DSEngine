#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameCamera.h"
#include <iostream>
#include <random>
#include <memory>
#include <utility>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "DSRenderer.h"
#include "Sprite.h"
#include "TileManager.h"
#include "SpriteComponent.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "InstrumentHandler.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 500;

float lastFrameTime = 0.0f;

float currentWindowWidth = 0.0f;
float currentWindowHeight = 0.0f;

glm::vec2 currentMousePos = glm::vec2(0.0f);

float targetWidth = SCR_WIDTH;
float targetHeight = SCR_HEIGHT;
float aspectRatio = targetWidth / targetHeight;

float zoom = 0.8f;

float deltaTime = 0.0f;

std::unique_ptr<GameCamera> MainCamera;
InputManager Input;

GLFWwindow* GameWindow = nullptr;
void processInput(GLFWwindow* window);
void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Init();
void Run();

int main()
{
    Init();

    Run();

    return EXIT_SUCCESS;
}

void Run()
{
    currentWindowWidth = SCR_WIDTH;
    currentWindowHeight = SCR_HEIGHT;
    TileManager m_TileManager("blocks.png", 16, 0);

    float viewPortRatio = SCR_WIDTH / SCR_HEIGHT;
    glEnable(GL_DEPTH_TEST);

    MainCamera = std::make_unique<GameCamera>(GameCamera());
    Input.AddAction("Exit", GLFW_KEY_ESCAPE);
    Input.AddAction("MoveUp", GLFW_KEY_W);
    Input.AddAction("MoveDown", GLFW_KEY_S);
    Input.AddAction("MoveLeft", GLFW_KEY_A);
    Input.AddAction("MoveRight", GLFW_KEY_D);
    Input.AddAction("Delete", GLFW_KEY_H);

    MainCamera->SetProjection(glm::ortho(
        0.0f,
        (float)SCR_WIDTH,
        (float)SCR_HEIGHT,
        0.0f,
        0.5f,
        1.0f));

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 5); // define the range

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int id = distr(gen);

            m_TileManager.CreateTile(1, glm::ivec2(x, y));
        }
    }

    m_TileManager.Initialize();

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
 


        float speed = deltaTime * 50.f;
        if (Input.IsPressed("MoveUp"))
        {
            MainCamera->Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        }

        if (Input.IsPressed("MoveDown"))
        {
            MainCamera->Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        }

        if (Input.IsPressed("MoveLeft"))
        {
            MainCamera->Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        if (Input.IsPressed("MoveRight"))
        {
            MainCamera->Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        MainCamera->Update();

        if (Input.IsPressedDown("Delete"))
        {
            double x = 2.0 * currentMousePos.x / currentWindowWidth - 1;
            double y = -1.0 * (currentMousePos.y / (currentWindowHeight / 2) - 1.0);
            
            glm::vec4 screenPos = glm::vec4(x, y, -0.5, 1.0f);
            std::cout << x << y << std::endl;
            glm::mat4 finalMat = MainCamera->Projection * MainCamera->View;

            glm::mat4 inverseMat = glm::inverse(finalMat);
            glm::vec3 worldPos = inverseMat * screenPos;
            std::cout << glm::to_string(worldPos) << std::endl;
            m_TileManager.ClearTile(glm::vec2(worldPos.x, worldPos.y));
        }
        // render
        // ------
        glClearColor(0.5f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   




        m_TileManager.Draw(MainCamera->Projection, MainCamera->View);

        //m_SpriteManager.Draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(GameWindow);
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    m_TileManager.Destroy();

    glfwDestroyWindow(GameWindow);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void Init()
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

void Tick()
{

}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    Input.PollInputs(window);
    if (Input.IsPressedDown("Exit"))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    currentMousePos = glm::vec2(xpos, ypos);
}

void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    currentWindowWidth = width;
    currentWindowHeight = height;
}