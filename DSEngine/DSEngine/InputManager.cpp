#include "InputManager.h"

void InputManager::PollInputs(GLFWwindow* window)
{
    for (const auto& action : m_Actions) {
        // Check if user just pressed
        if (glfwGetKey(window, action.second.KeyCode) == GLFW_PRESS)
        {
            m_Actions[action.first].Pressed = true;
            m_Actions[action.first].IsPressedDown = true;
        }
        // if it was already pressed down
        else if (action.second.IsPressedDown)
        {
            // Reset for this frame
            m_Actions[action.first].IsPressedDown = false;
        }

        if (m_Actions[action.first].Pressed && glfwGetKey(window, action.second.KeyCode) == GLFW_RELEASE)
        {
            m_Actions[action.first].Pressed = false;
            m_Actions[action.first].IsPressedUp = true;
        }
        // if it was already pressed down
        else if (action.second.IsPressedUp)
        {
            // Reset for this frame
            m_Actions[action.first].IsPressedUp = false;
        }
    }
}



void InputManager::AddAction(std::string action, int keyCode)
{
    // If Not found
    if (m_Actions.find(action) == m_Actions.end()) {
        // Create new Action
        m_Actions[action] = { keyCode };
    }
}

void InputManager::EditAction(std::string action, int keycode)
{
    if (m_Actions.find(action) != m_Actions.end()) {
        // Create new Action
        m_Actions[action].KeyCode = keycode;
    }
}

bool InputManager::IsPressed(std::string action)
{
    if (m_Actions.find(action) != m_Actions.end()) {
        // Create new Action
        return m_Actions[action].Pressed;
    }

    return false;
}

bool InputManager::IsPressedDown(std::string action)
{
    if (m_Actions.find(action) != m_Actions.end()) {
        // Create new Action
        return m_Actions[action].IsPressedDown;
    }
    return false;
}

bool InputManager::IsPressedUp(std::string action)
{
    if (m_Actions.find(action) != m_Actions.end()) {
        // Create new Action
        return m_Actions[action].IsPressedUp;
    }

    return false;
}