#pragma once
#include <memory>
#include "GameCamera.h"
#include "InputManager.h"

extern GLFWwindow* E_GameWindow;

extern float E_DeltaTime;

extern std::unique_ptr<GameCamera> MainCamera;

extern std::unique_ptr<InputManager> Input;