#include "DSEngine.h"

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
    
    MainCamera = std::make_unique<GameCamera>(GameCamera());
    Input = std::make_unique<InputManager>(InputManager());
    Input->AddAction("Exit", GLFW_KEY_ESCAPE);
    Input->AddAction("MoveUp", GLFW_KEY_W);
    Input->AddAction("MoveDown", GLFW_KEY_S);
    Input->AddAction("MoveLeft", GLFW_KEY_A);
    Input->AddAction("MoveRight", GLFW_KEY_D);
    
    MainCamera->SetProjection(glm::ortho(
        -aspectRatio * 500.f * zoom,
        aspectRatio * 500.f * zoom,
        -500.f * zoom,
        500.f * zoom,
        -1.0f,
        1.0f));
 
    Sprite sprite = {};

    std::vector<SpriteComponent> components;

    for (int i = 0; i < 10000; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Entity* entity = new Entity("Wall" + i);
        entity->Size = glm::vec2(10.f, 10.f);
        
        SpriteComponent spriteComp(entity, glm::vec3(r, g, b));

        spriteComp.AssignSprite(&sprite);
        spriteComp.AssignShader(&spriteShader);

        components.push_back(spriteComp);


        entity->AddComponent(&spriteComp);
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-200, 200); // define the range

        int posX = distr(gen);
        int posY = distr(gen);
        m_EntityManager.AddEntity(entity);
        entity->Position = glm::vec2((float)posX, (float)posY);
    }

    sprite.Initialize("wall.jpg", false, &spriteShader);

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

        float speed = E_DeltaTime * 50.f;
        if (Input->IsPressed("MoveUp"))
        {
            MainCamera->Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        }

        if (Input->IsPressed("MoveDown"))
        {
            MainCamera->Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        }

        if (Input->IsPressed("MoveLeft"))
        {
            MainCamera->Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        if (Input->IsPressed("MoveRight"))
        {
            MainCamera->Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        }

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainCamera->Update();
        m_EntityManager.Update();

        sprite.Draw();

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
    Input->PollInputs(window);
    if (Input->IsPressedDown("Exit"))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    MainCamera->UpdateMouse(window, xpos, ypos);
}