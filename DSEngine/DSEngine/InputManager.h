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
    std::map<std::string, Action> m_Actions;

public:
    void AddAction(std::string action, int keycode);
    void EditAction(std::string action, int keycode);

    bool IsPressed(std::string action);
    bool IsPressedDown(std::string action);
    bool IsPressedUp(std::string action);

    void PollInputs(GLFWwindow* window);
};

