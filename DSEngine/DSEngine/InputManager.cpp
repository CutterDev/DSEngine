#include "InputManager.h"

void InputManager::PollInputs(GLFWwindow* window)
{
    for (const auto& action : m_Actions) {
        // Check if user just pressed
        if (glfwGetKey(window, action.second.KeyCode) == GLFW_PRESS)
        {
            if (!m_Actions[action.first].Pressed)
            {
                m_Actions[action.first].IsPressedDown = true;
            }
            else
            {
                m_Actions[action.first].IsPressedDown = false;
            }

            m_Actions[action.first].Pressed = true;
        }

        if (glfwGetKey(window, action.second.KeyCode) == GLFW_RELEASE)
        {
            if (m_Actions[action.first].Pressed)
            {
                m_Actions[action.first].IsPressedUp = true;
            }
            else
            {
                m_Actions[action.first].IsPressedUp = false;
            }
            m_Actions[action.first].Pressed = false;
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