#include "Camera.h"

Camera::Camera(
    glm::vec3 initialPos,
    glm::vec3 initialFront,
    glm::vec3 initialUp,
    float initialFov,
    float initialMovementSensitivity,
    float initialCameraSensititvity
) 
    : cameraPos(initialPos), cameraFront(initialFront), cameraUp(initialUp),
      fov(initialFov), movementSensitivity(initialMovementSensitivity),
      cameraSensitivity(initialCameraSensititvity)
{
    updateCameraVectors();
}

void Camera::handleCameraMovement(GLFWwindow* window, float deltaTime)
{
    const float cameraSpeed = movementSensitivity * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::handleCameraRotation(GLFWwindow* window, double xpos, double ypos)
{
    float xposf = (float)xpos;
    float yposf = (float)ypos;

    if (firstMouse)
    {
        lastX = xposf;
        lastY = yposf;
        firstMouse = false;
    }

    float xoffset = xposf - lastX;
    float yoffset = lastY - yposf; // reversed since y-coordinates range from bottom to top
    lastX = xposf;
    lastY = yposf;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::handleMouseScrollZoom(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

glm::mat4 Camera::lookAt() const
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(newFront);
}