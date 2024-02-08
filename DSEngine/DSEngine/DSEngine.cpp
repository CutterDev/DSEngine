#include "DSEngine.h"

GameCamera Camera;

float E_DeltaTime = 0.0f;

void DSEngine::Run()
{
    m_Renderer.Initialize(SCR_WIDTH, SCR_HEIGHT);
    Shader cubeShader("shader.vs", "shader.fs");
    Shader floorShader("shader.vs", "shader.fs");
    Shader lightShader("shader.vs", "lightsource.fs");

    Camera.TranslateView(glm::vec3(0.0f, 0.0f, -3.0f));
    Camera.SetProjection(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
    float lastFrameTime = 0.0f;

    BasicCubeNode lightNode;
    lightNode.m_Shader = &lightShader;

    GameObject lightCube;
    lightCube.AddNode(&lightNode);
    lightCube.Translate(-2.0f, 2.0f, -6.0f);

    GameObject basicCube;

    basicCube.Translate(0.0f, 2.0f, -5.0f);

    // Todo: Try to find a way so the Vertex Arrays aren't repeated for the same vertices for the same type of node.
    BasicCubeNode node = BasicCubeNode();

    node.m_Shader = &cubeShader;

    basicCube.AddNode(&node);

    GameObject basicCube2;
    basicCube.Rotate(45.0f, glm::vec3(10.0f, 0.0f, 0.0f));
    basicCube2.Translate(0.0f, 0.0f, -5.0f);
    basicCube2.AddNode(&node);
    basicCube2.Parent = &basicCube;


    GameObject floor;
    floor.Scale(glm::vec3(100.0f, 1.0f, 100.0f));
    floor.Translate(0.0, -2.0f, 0.0f);
    floor.AddNode(&node);


    GameObject pivotPoint;
    lightCube.Parent = &pivotPoint;

    // render loop
    // -----------
    while (!m_Renderer.WindowShouldClose())
    {
        float currentFrameTime = glfwGetTime();
        E_DeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        cubeShader.Use();
        cubeShader.SetVec3("objectColor", 0.1f, 0.4f, 1.0f);
        cubeShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.SetVec3("lightPos", lightCube.Position());

        // input
        // -----
        processInput(E_GameWindow);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.Use();
        cubeShader.SetVec3("objectColor", 0.1f, 0.4f, 1.0f);
        cubeShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.SetVec3("lightPos", lightCube.Position());
        cubeShader.SetVec3("viewPos", Camera.Position);

        Camera.Update();
        glBindVertexArray(node.m_VAO);
        basicCube.Update(&Camera);
        basicCube2.Update(&Camera);
        lightCube.Update(&Camera);


        floor.Update(&Camera);

        //pivotPoint.Rotate(20.0f * deltaTime, glm::vec3(45.0f, 45.0f, 0.0f));

        // glBindVertexArray(0); // no need to unbind it every time 

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