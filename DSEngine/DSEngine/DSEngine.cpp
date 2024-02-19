#include "DSEngine.h"

std::unique_ptr<GameCamera> MainCamera;
InputManager Input;
float lastFrameTime = 0.0f;

float targetWidth = 640.f;
float targetHeight = 360.f;
float aspectRatio = targetWidth / targetHeight;

float zoom = 0.5f;

GLFWwindow* GameWindow;
void processInput(GLFWwindow* window);
void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);

void DSEngine::Run()
{
    Init();
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
    //for (int i = 0; i < 200000; i++)
    //{
    //    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //    Entity* entity = new Entity("Wall" + i);
    //    entity->Size = glm::vec2(10.f, 10.f);

    //    std::random_device rd; // obtain a random number from hardware
    //    std::mt19937 gen(rd()); // seed the generator
    //    std::uniform_int_distribution<> distr(-300, 300); // define the range

    //    int posX = distr(gen);
    //    int posY = distr(gen);
    //    m_EntityManager.AddEntity(entity);
    //    entity->Position = glm::vec2((float)posX, (float)posY);
    //}

    m_TileManager = new TileManager("blocks.png", 32, 1);

    m_TileManager->CreateTile(1, glm::vec2(1, 1));
    m_TileManager->Initialize();

       double previousTime = glfwGetTime();
    int frameCount = 0;

    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(GameWindow))
    {
        float currentFrameTime = glfwGetTime();
        E_DeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Measure speed
        frameCount++;
        // If a second has passed.
        if (currentFrameTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.
            std::cout << "==================" << std::endl;
            std::cout<< frameCount << std::endl;

            frameCount = 0;
            previousTime = currentFrameTime;
        }


        // input
        // -----
        processInput(GameWindow);

        float speed = E_DeltaTime * 50.f;
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

  
        m_TileManager->Draw(MainCamera->Projection, MainCamera->View);

        //m_SpriteManager.Draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(GameWindow);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    m_TileManager->Destroy();


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void DSEngine::Init()
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
    glfwMakeContextCurrent(GameWindow);
    if (GameWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetInputMode(GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(GameWindow, Framebuffer_Size_Callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void DSEngine::Tick()
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