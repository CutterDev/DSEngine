#include "InputManager.h"
std::map<std::string, Action> InputManager::m_Actions;
void InputManager::PollInputs(GLFWwindow* window)
{
    for (const auto& action : InputManager::m_Actions) {
        // Check if user just pressed
        if (glfwGetKey(window, action.second.KeyCode) == GLFW_PRESS)
        {
            if (!InputManager::m_Actions[action.first].Pressed)
            {
                InputManager::m_Actions[action.first].IsPressedDown = true;
            }
            else
            {
                InputManager::m_Actions[action.first].IsPressedDown = false;
            }

            InputManager::m_Actions[action.first].Pressed = true;
        }

        if (glfwGetKey(window, action.second.KeyCode) == GLFW_RELEASE)
        {
            if (InputManager::m_Actions[action.first].Pressed)
            {
                InputManager::m_Actions[action.first].IsPressedUp = true;
            }
            else
            {
                InputManager::m_Actions[action.first].IsPressedUp = false;
            }
            InputManager::m_Actions[action.first].Pressed = false;
        }
    }
}



void InputManager::AddAction(std::string action, int keyCode)
{
    // If Not found
    if (InputManager::m_Actions.find(action) == InputManager::m_Actions.end()) {
        // Create new Action
        InputManager::m_Actions[action] = { keyCode };
    }
}

void InputManager::EditAction(std::string action, int keycode)
{
    if (InputManager::m_Actions.find(action) != InputManager::m_Actions.end()) {
        // Create new Action
        InputManager::m_Actions[action].KeyCode = keycode;
    }
}

bool InputManager::IsPressed(std::string action)
{
    if (InputManager::m_Actions.find(action) != InputManager::m_Actions.end()) {
        // Create new Action
        return InputManager::m_Actions[action].Pressed;
    }

    return false;
}

bool InputManager::IsPressedDown(std::string action)
{
    if (InputManager::m_Actions.find(action) != InputManager::m_Actions.end()) {
        // Create new Action
        return InputManager::m_Actions[action].IsPressedDown;
    }
    return false;
}

bool InputManager::IsPressedUp(std::string action)
{
    if (InputManager::m_Actions.find(action) != InputManager::m_Actions.end()) {
        // Create new Action
        return InputManager::m_Actions[action].IsPressedUp;
    }

    return false;
}