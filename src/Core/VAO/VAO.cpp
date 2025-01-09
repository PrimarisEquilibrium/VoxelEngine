#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    bind();
}

void VAO::bind() const {
    glBindVertexArray(ID);
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::remove() const {
    glDeleteVertexArrays(1, &ID);
}