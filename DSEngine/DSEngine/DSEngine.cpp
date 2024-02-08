#include "DSEngine.h"

GameCamera Camera;

float E_DeltaTime = 0.0f;
float lastFrameTime = 0.0f;

void DSEngine::Run()
{
    m_Renderer.Initialize(SCR_WIDTH, SCR_HEIGHT);
    Shader cubeShader("shader.vs", "shader.fs");
    Shader floorShader("shader.vs", "shader.fs");
    Shader lightShader("shader.vs", "lightsource.fs");

    Camera.TranslateView(glm::vec3(0.0f, 0.0f, -3.0f));
    Camera.SetProjection(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));


    // render loop
    // -----------
    while (!m_Renderer.WindowShouldClose())
    {
        float currentFrameTime = glfwGetTime();
        E_DeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // input
        // -----
        processInput(E_GameWindow);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Camera.Update();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(E_GameWindow);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    cubeShader.Delete();
    lightShader.Delete();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void DSEngine::Tick()
{

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Camera.MovementUpdate(window, E_DeltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera.UpdateMouse(window, xpos, ypos);
}