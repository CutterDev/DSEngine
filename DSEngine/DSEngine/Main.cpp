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
#include "DefaultCube.h"
#include "MeshFilter.h"
#include "MeshNode.h"
//#include "ModelImporter.h"

GameCamera Camera;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;

int main()
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSwapInterval(0);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader cubeShader("shader.vs", "shader.fs");
    Shader floorShader("shader.vs", "shader.fs");
    Shader lightShader("shader.vs", "lightsource.fs");

    Material material;
    material.Shader = &cubeShader;
    material.Shininess = 32.0f;
    material.Ambient = glm::vec3(0.31f, 0.5f, 1.0f);
    material.Diffuse = glm::vec3(0.31f, 0.5f, 1.0f);
    material.Specular = glm::vec3(0.5f, 0.5f, 0.5f);

    Camera.TranslateView(glm::vec3(0.0f, 0.0f, -3.0f));
    Camera.SetProjection(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f));
    float lastFrameTime = 0.0f;



    GameObject lightCube;
    GameObject basicCube;

    basicCube.Translate(0.0f, 2.0f, -5.0f);

    // Todo: Try to find a way so the Vertex Arrays aren't repeated for the same vertices for the same type of node.
    DefaultCube cube;

    MeshNode mesh1;
    mesh1.MeshFilter = &cube;
    mesh1.Material = &material;
    MeshNode mesh2;
    mesh2.MeshFilter = &cube;
    mesh2.Material = &material;
    MeshNode mesh3;
    mesh3.MeshFilter = &cube;
    mesh3.Material = &material;

    lightCube.Translate(-2.0f, 2.0f, -6.0f);

    basicCube.AddNode(&mesh1);

    GameObject basicCube2;
    basicCube.Rotate(45.0f, glm::vec3(10.0f, 0.0f, 0.0f));
    basicCube2.Translate(0.0f, 0.0f, -5.0f);
    basicCube2.AddNode(&mesh2);
    basicCube2.Parent = &basicCube;



    GameObject floor;
    floor.Scale(glm::vec3(100.0f, 1.0f, 100.0f));
    floor.Translate(0.0, -2.0f, 0.0f);
    floor.AddNode(&mesh3);


    GameObject pivotPoint;
    lightCube.Parent = &pivotPoint;

    //ModelImporter model;

    //model.Import();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        cubeShader.Use();
        cubeShader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        cubeShader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        cubeShader.SetVec3("light.specular", 0.1f, 0.1f, 0.1f);
        cubeShader.SetVec3("light.position", lightCube.Position());
        cubeShader.SetVec3("viewPos", Camera.Position);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.Use();
        cubeShader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        cubeShader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        cubeShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
        cubeShader.SetVec3("light.position", lightCube.Position());
        cubeShader.SetVec3("viewPos", Camera.Position);


        basicCube.Update(&Camera);
        basicCube2.Update(&Camera);
        lightCube.Update(&Camera);


        floor.Update(&Camera);

        //pivotPoint.Rotate(20.0f * deltaTime, glm::vec3(45.0f, 45.0f, 0.0f));

        // glBindVertexArray(0); // no need to unbind it every time 
        
        Camera.Update(deltaTime);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    cubeShader.Delete();
    lightShader.Delete();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Camera.MovementUpdate(window);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera.UpdateMouse(window, xpos, ypos);
}