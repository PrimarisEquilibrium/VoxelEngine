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

// Ensure the shader compiled successfully
void validateShaderCompilation(unsigned int vertexShader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/* A simple vertex shader */
const char* vertexShaderSource = (
    // Define the GLSL (OpenGL shader language) version to 3.3
    "#version 330 core\n"

    // Declare the vertex data attributes (in a vector3 in this case, x, y, z)
    // Also store the input variable using layout (location = 0)
    "layout (location = 0) in vec3 aPos;\n"

    // Whatever gl_Position is will be the output of the vertex shader
    // Set the gl_Position to the vertex position, with perspective division (fourth dimension) to 1
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
);

/* A simple fragment shader */
const char* fragmentShaderSource = (
    "#version 330 core\n"
    "out vec4 FragColor;\n"    

    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\0"
);

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
    // The OpenGL context is an environment for all state and resources for OpenGL to render
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


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    /* Vertices are transformed to NDC in the vertex shader, any vertices outside
       the interval [-1, 1] are clipped */

    /* Create the vertex buffer object */
    // Holds the id of the buffer
    unsigned int VBO;

    // Generating the buffer (1 is the number of buffers to create, VBO stores the id)
    glGenBuffers(1, &VBO);

    /* Create the vertex array object, acts like a storage for VBO configuration */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Bind the vertex array object
    glBindVertexArray(VAO);

    // GL_ARRAY_BUFFER is the buffer object for vertex buffer objects, and it is
    // binded to VBO. By binding it whatever operation we perform on the GL_ARRAY_BUFFER
    // affects the VBO buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // glBufferData lets us send user-defined data into the currently bound buffer
    // First argument: Type of buffer we want to send data into
    // Second argument: The size of the data we want to pass into the buffer (in bytes)
    // Third argument: The data to send into the buffer
    // Fourth Argument: How we want the GPU to manage the given data:
    /* GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
       GL_STATIC_DRAW: the data is set only once and used many times.
       GL_DYNAMIC_DRAW: the data is changed a lot and used many times. */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Let OpenGL know how to interpret our vertex attributes */
    // First argument: The location index of the vertex attribute we want to configure, layout (location = 0) earlier
    // Second argument: The size of the vertex attribute, vec3 is composed of 3 values
    // Third argument: The type of data being stored
    // Fourth argument: Whether or not the data is normalized (not relevant if you're working with floats)
    // Fifth argument: The stride, the space inbetween consecutive vertex attributes
    // Sixth argument: The offset from the start of the data array (type is void*)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Enable the position (vec3) to be used for the vertex shader during rendering
    glEnableVertexAttribArray(0);
    

    /* Create the vertex shader */
    // The id that references the vertex shader
    unsigned int vertexShader;

    // Create an OpenGL shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Sets the vertex shader to have the source code we wrote
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile the shader
    glCompileShader(vertexShader);

    // Ensure the vertex shader compiled properly
    validateShaderCompilation(vertexShader);


    /* Create the fragment shader */
    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    // Ensure the fragment shader compiled properly
    validateShaderCompilation(vertexShader);


    /* Create a shader program object, a shader program object is the final linked
       version of multiple shaders combined. */
    unsigned int shaderProgram;

    // Create the shader program
    shaderProgram = glCreateProgram();

    // Attach the shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Active the shader program
    // All rendering calls after this line of code will use this shader program object
    glUseProgram(shaderProgram);


    /* Vertex buffer objects allow you to send large batches of vertex data to the GPU's memory 
       directly rather than one by one with the CPU */

    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draws an array of vertices, takes a primitive, starting index, and # of vertices to draw
        glDrawArrays(GL_TRIANGLES, 0, 3);

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