#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
    GLsizei length, const char* message, const void* userParam);

class DSRenderer
{
public:
    void Initialize(int width, int height);
    bool WindowShouldClose();
    void End();
};