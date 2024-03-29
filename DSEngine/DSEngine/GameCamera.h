#ifndef GAMECAMERA_H
#define GAMECAMERA_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class GameCamera
{
private:
    bool m_FirstMouse = false;
    float m_CameraSpeed = 50.0f;
    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;
    glm::vec3 m_CameraRight;
    float m_Size = 800.f;
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;
    float m_LastX = 800.0f / 2.0;
    float m_LastY = 600.0 / 2.0;
    float m_Fov = 45.0f;

    int m_CurrentWindowHeight = 0;
    int m_CurrentWindowWidth = 0;
public:
    glm::vec3 Position;
    glm::mat4 Projection;
    glm::mat4 View;

    GameCamera() 
    { 
        Projection = glm::mat4(0.0f); 
        View = glm::mat4(0.0f); 
        Position = glm::vec3(0.0f, 0.0f, 1.f);
        m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void Initialize(int windowWidth, int windowHeight)
    {
        m_CurrentWindowWidth = windowWidth;
        m_CurrentWindowHeight = windowHeight;
    }
    void TranslateView(glm::vec3 pos)
    {
        View = glm::translate(View, pos);
    }

    void Translate(glm::vec3 pos)
    {
        Position += pos;
    }

    void SetProjection(float width, float height, float aspect)
    {
        m_CurrentWindowWidth = width;
        m_CurrentWindowHeight = height;

        float xs = aspect > 1.f ? aspect : 1.f;
        float sy = aspect > 1.f ? 1.0 : 1.0f / aspect;

        Projection =glm::ortho(
                -(width / 2.f),
                (width / 2.f),
                -(height / 2.f),
                (height / 2.f),
                0.1f,
                10.0f);
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

    glm::vec3 ScreenToWorldPos(glm::vec2 mousePos)
    {
        double x = 2.0 * mousePos.x / m_CurrentWindowWidth - 1;
        double y = -1.0 * (mousePos.y / (m_CurrentWindowHeight / 2) - 1.0);

        glm::vec4 screenPos = glm::vec4(x, y, -0.5, 1.0f);
        glm::mat4 finalMat = Projection * View;

        glm::mat4 inverseMat = glm::inverse(finalMat);
        glm::vec3 worldPos = inverseMat * screenPos;

        return worldPos;
    }

    glm::vec2 WorldPosToScreenSpace(glm::vec3 worldPos)
    {
        glm::vec4 clipSpace = Projection * (View * glm::vec4(worldPos, 1.0));
        if (clipSpace.w != 0.f)
        {
            glm::vec2 windowSize = glm::vec2(m_CurrentWindowWidth, m_CurrentWindowHeight);
            glm::vec3 ndcSpace = glm::vec3(clipSpace) / clipSpace.w;

            glm::vec2 windowSpacePos = ((glm::vec2(ndcSpace) + 1.0f) / 2.0f) * windowSize;
        
            return windowSpacePos;
        }

        return glm::vec2(-10000.f);
    }
};
#endif