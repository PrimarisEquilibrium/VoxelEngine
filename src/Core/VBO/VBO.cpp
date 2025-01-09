#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove() const {
    glDeleteBuffers(1, &ID);
}