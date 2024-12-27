#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* Every time the window is resized we need to adjust the OpenGL viewport */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/* Process input using GLFW */
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    
    // GLFW fails to run if the user doesn't have OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // GLFW will use a smaller subset of OpenGL features without unneccesary backwards-compatible features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Voxel Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD, load OpenGL function pointers at runtime
    // gladLoadGLLoader - loads all the OpenGL function pointers in memory
    // glfwGetProcAddress - retrieves the address of OpenGL functions from the driver
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // First two arguments set the top left corner of the window
    // Second two arguments set the width and height of the rendering window
    glViewport(0, 0, 800, 600);

    /* Under the hood OpenGL uses glViewport to map normalized device coordinates
       to pixel-based screen coordinates. */

    // Let GLFW know the callback function when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* A frame buffer stores the pixel information in a frame, the frame buffer size
       is the width and the height of the screen */

    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swaps the color buffer with the one that was just rendered
        glfwSwapBuffers(window);

        // Updates the window state and calls corresponding event callback functions
        glfwPollEvents();
    }

    /* glfwSwapBuffers uses a double buffer system where all rendering is done
       on a back buffer and then is swapped to the front buffer when completed */

    // Clear all GLFW resources
    glfwTerminate();
    return 0;
}