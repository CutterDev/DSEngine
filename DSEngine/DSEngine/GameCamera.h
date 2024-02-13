#ifndef GAMECAMERA_H
#define GAMECAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class GameCamera
{
private:
    bool m_FirstMouse = false;
    float m_CameraSpeed = 50.0f;
    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;
    glm::vec3 m_CameraRight;
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;
    float m_LastX = 800.0f / 2.0;
    float m_LastY = 600.0 / 2.0;
    float m_Fov = 45.0f;
public:
    glm::vec3 Position;
    glm::mat4 Projection;
    glm::mat4 View;

    GameCamera() 
    { 
        Projection = glm::mat4(0.0f); 
        View = glm::mat4(0.0f); 
        Position = glm::vec3(0.0f, 0.0f, 0.5f);
        m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void TranslateView(glm::vec3 pos)
    {
        View = glm::translate(View, pos);
    }

    void Translate(glm::vec3 pos)
    {
        Position += pos;
    }

    void SetProjection(glm::highp_mat4 mat4)
    {
        Projection = mat4;
    }
    
    void Update()
    {
        View = glm::lookAt(Position, Position + m_CameraFront, m_CameraUp);
    }
    void UpdateMouse(GLFWwindow* window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (m_FirstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_FirstMouse = false;
        }

        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top
        m_LastX = xpos;
        m_LastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // make sure that when Pitch is out of bounds, screen doesn't get flipped
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_CameraFront = glm::normalize(front);
    }
};
#endif