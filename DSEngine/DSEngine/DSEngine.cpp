#include "DSEngine.h"

GameCamera Camera;

float E_DeltaTime = 0.0f;
float lastFrameTime = 0.0f;

float targetWidth = 640.f;
float targetHeight = 360.f;
float aspectRatio = targetWidth / targetHeight;

float zoom = 0.5f;
void DSEngine::Run()
{
    float viewPortRatio = SCR_WIDTH / SCR_HEIGHT;
    m_Renderer.Initialize(SCR_WIDTH, SCR_HEIGHT);
    Shader spriteShader("sprite.vs", "sprite.fs");

    Camera.SetProjection(glm::ortho(
        -aspectRatio * 500.f * zoom,
        aspectRatio * 500.f * zoom,
        -500.f * zoom,
        500.f * zoom,
        -1.0f,
        1.0f));
 
    Entity entity("Wall");
    entity.Size = glm::vec2(100.f, 100.f);
    SpriteComponent spriteComp(&entity);
    Sprite sprite = {};
    sprite.Initialize("wall.jpg", false, &spriteShader);

    spriteComp.AssignSprite(&sprite);
    spriteComp.AssignShader(&spriteShader);

    entity.AddComponent(spriteComp);

    m_EntityManager.AddEntity(entity);

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
        spriteShader.Use();
        spriteShader.SetMat4("projection", Camera.Projection);
        spriteShader.SetMat4("view", Camera.View);
        m_EntityManager.Update();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(E_GameWindow);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

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