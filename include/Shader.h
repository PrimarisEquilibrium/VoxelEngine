#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>

class Shader 
{
public:
    // The ID/handler of the shader.
    unsigned int ID;

    /**
     * Constructor generates the shader.
     * 
     * @param vertexPath The path to the vertex shader file.
     * @param fragmentPath The path to the fragment shader file.
     */
    Shader(const char* vertexPath, const char* fragmentPath);

    // Activate the shader
    void use();

    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
private:
    // Utility function for checking shader compilation/linking errors
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif