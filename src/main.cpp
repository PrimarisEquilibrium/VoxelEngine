#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shader.h"
#include "Core/Texture/Texture.h"

#include <iostream>

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>


// Constants
const unsigned int sWIDTH = 800;
const unsigned int sHEIGHT = 600;
const unsigned int FOV = 60;
const char* TEXTURE_ATLAS = ".\\public\\textures\\texture_atlas.png";

// Computed variables
const float ASPECT_RATIO = (float)sWIDTH / (float)sHEIGHT;

// Camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float fov = 45.0f;

// Time variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Every time the window is resized we need to adjust the OpenGL viewport */
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/* Process input using GLFW */
static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

float lastX = 400.0f, lastY = 300.0f;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

int main() {
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(sWIDTH, sHEIGHT, "Voxel Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // Configure global OpenGL state
    glEnable(GL_TEXTURE_3D);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    /* Create textures */
    Texture texture(GL_TEXTURE_2D, GL_TEXTURE0);
    texture.bind();
    texture.load(TEXTURE_ATLAS, GL_RGB);

    auto [dirtX, dirtY] = texture.getTexelOffset(TextureType::Dirt);
    auto [grassSX, grassSY] = texture.getTexelOffset(TextureType::GrassSide);
    auto [grassTX, grassTY] = texture.getTexelOffset(TextureType::GrassTop);
    
    float vertices[] = {
         // Position          // Texture   // Texture Offset
         // Front face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  grassSX, grassSY,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  grassSX, grassSY,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  grassSX, grassSY,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  grassSX, grassSY,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  grassSX, grassSY,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  grassSX, grassSY,

        // Back face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  grassSX, grassSY,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  grassSX, grassSY,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  grassSX, grassSY,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  grassSX, grassSY,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  grassSX, grassSY,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  grassSX, grassSY,

         // Left face
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  grassSX, grassSY,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  grassSX, grassSY,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  grassSX, grassSY,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  grassSX, grassSY,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  grassSX, grassSY,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  grassSX, grassSY,

         // Right face
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  grassSX, grassSY,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  grassSX, grassSY,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  grassSX, grassSY,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  grassSX, grassSY,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  grassSX, grassSY,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  grassSX, grassSY,

         // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  dirtX, dirtY,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  dirtX, dirtY,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  dirtX, dirtY,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  dirtX, dirtY,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  dirtX, dirtY,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  dirtX, dirtY,

         // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  grassTX, grassTY,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  grassTX, grassTY,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  grassTX, grassTY,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  grassTX, grassTY,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  grassTX, grassTY,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  grassTX, grassTY,
    };

    /* Create vertex array object and all associated configurations */
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Offset
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /* Create shader */
    Shader shader(".\\public\\shaders\\vertex.glsl", ".\\public\\shaders\\fragment.glsl");
    shader.use();
    shader.setInt("texture", 0);
    shader.setFloat("atlasHeight", 1024.0);
    shader.setFloat("tileSize", (float)texture.TILE_SIZE);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        for (int i = 0; i < 6; i++) {

            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            projection = glm::perspective(glm::radians(fov), ASPECT_RATIO, 0.1f, 100.0f);

            shader.setMat4("model", model);
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
            glDrawArrays(GL_TRIANGLES, i * 6, 6);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}