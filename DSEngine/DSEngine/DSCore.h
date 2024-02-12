#pragma once
#include <memory>
#include "GameCamera.h"
extern GLFWwindow* E_GameWindow;

extern float E_DeltaTime;

extern std::unique_ptr<GameCamera> MainCamera;