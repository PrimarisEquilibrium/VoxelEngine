#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
    // VBO ID
    GLuint ID;

    // Constructor for VBO
    VBO(GLfloat* vertices, GLsizeiptr size);
    
    // Binds the VBO to GL_ARRAY_BUFFER
    void bind() const;

    // Unbinds the VBO
    void unbind() const;

    // Deletes the VBO
    void remove() const;
};

#endif