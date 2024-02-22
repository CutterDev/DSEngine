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

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float lastFrameTime = 0.0f;

float targetWidth = 640.f;
float targetHeight = 360.f;
float aspectRatio = targetWidth / targetHeight;

float zoom = 0.5f;

float deltaTime = 0.0f;

std::unique_ptr<GameCamera> MainCamera;
InputManager Input;

GLFWwindow* GameWindow = nullptr;
void processInput(GLFWwindow* window);
void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);

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
    TileManager m_TileManager("blocks.png", 16, 0);

    float viewPortRatio = SCR_WIDTH / SCR_HEIGHT;
    glEnable(GL_DEPTH_TEST);

    MainCamera = std::make_unique<GameCamera>(GameCamera());
    Input.AddAction("Exit", GLFW_KEY_ESCAPE);
    Input.AddAction("MoveUp", GLFW_KEY_W);
    Input.AddAction("MoveDown", GLFW_KEY_S);
    Input.AddAction("MoveLeft", GLFW_KEY_A);
    Input.AddAction("MoveRight", GLFW_KEY_D);

    MainCamera->SetProjection(glm::ortho(
        -aspectRatio * 500.f * zoom,
        aspectRatio * 500.f * zoom,
        -500.f * zoom,
        500.f * zoom,
        -1.0f,
        1.0f));

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 5); // define the range

    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            int id = distr(gen);

            m_TileManager.CreateTile(id, glm::ivec2(x, y));
        }
    }

    //for (int i = 0; i < 100; i++)
    //{
    //    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    //    std::random_device rd; // obtain a random number from hardware
    //    std::mt19937 gen(rd()); // seed the generator
    //    std::uniform_int_distribution<> distr(0, 50); // define the range

    //    int posX = distr(gen);
    //    int posY = distr(gen);
    //    m_TileManager.CreateTile(34, glm::vec2(posX, posY));
    //}

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
            MainCamera->Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        }

        if (Input.IsPressed("MoveDown"))
        {
            MainCamera->Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        }

        if (Input.IsPressed("MoveLeft"))
        {
            MainCamera->Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        if (Input.IsPressed("MoveRight"))
        {
            MainCamera->Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        // render
        // ------
        glClearColor(0.5f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   

        MainCamera->Update();


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
    MainCamera->UpdateMouse(window, xpos, ypos);
}

void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}