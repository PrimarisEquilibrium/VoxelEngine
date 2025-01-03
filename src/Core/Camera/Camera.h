#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>


class Camera
{
public:
    // Camera variables
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float fov;
    float movementSensitivity;
    float cameraSensitivity;
    float yaw = -90.0f;
    float pitch = 0.0f;

    // Mouse value pointers
    float lastX = 400.0f, lastY = 300.0f;
    bool firstMouse = true;

    // Constructor for the camera class.
    Camera(
        glm::vec3 initialPos,
        glm::vec3 initialFront,
        glm::vec3 initialUp,
        float initialFov,
        float initialMovementSensitivity,
        float initialCameraSensititvity
    );

    /**
     * Moves the camera in four directions using the WASD keys.
     * 
     * @param window The window to read key inputs from.
     * @param deltaTime The current deltaTime.
     */
    void handleCameraMovement(GLFWwindow* window, float deltaTime);

    /**
     * Rotates the camera left and right (yaw) & up and down (pitch)
     * 
     * @param window The window to read cursor movement inputs from.
     * @param xpos X-position of the cursor.
     * @param ypos Y-position of the cursor.
     */
    void handleCameraRotation(GLFWwindow* window, double xpos, double ypos);

    /**
     * Zooms the screen (decreases and increases the fov) based on the scroll wheel.
     * 
     * @param window The window to read scroll wheel movement from.
     * @param xoffset The x-offset of the scroll wheel.
     * @param yoffset The y-offset of the scroll wheel.
     */
    void handleMouseScrollZoom(GLFWwindow* window, double xoffset, double yoffset);

    // Returns the lookAt matrix for the camera
    glm::mat4 lookAt() const;

    // Updates the vector direction of where the camera is currently facing.
    void updateCameraVectors();
};

#endif