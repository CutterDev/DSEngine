#include "DSCore.h"

float E_DeltaTime = 0.0f;
GLFWwindow* E_GameWindow;
std::unique_ptr<GameCamera> MainCamera;
std::unique_ptr<InputManager> Input;