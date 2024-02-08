#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "DSCore.h"

class DSRenderer
{
public:
    void Initialize(int width, int height);
    bool WindowShouldClose();
};