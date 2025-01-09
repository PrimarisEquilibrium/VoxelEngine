#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO {
public:
    GLuint ID;

    VAO();

    void bind() const;
    void unbind() const;
    void remove() const;
};

#endif