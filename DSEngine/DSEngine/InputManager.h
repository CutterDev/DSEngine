#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <cctype>
#include <iostream>

struct Action {
public:
    int KeyCode;
    bool Pressed;
    bool IsPressedDown;
    bool IsPressedUp;
};
class InputManager
{
private:
    static std::map<std::string, Action> m_Actions;

public:
    static void AddAction(std::string action, int keycode);
    static void EditAction(std::string action, int keycode);

    static bool IsPressed(std::string action);
    static bool IsPressedDown(std::string action);
    static bool IsPressedUp(std::string action);

    static void PollInputs(GLFWwindow* window);
};

