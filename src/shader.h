#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{
public:
    Shader(const std::string &filename);

    void Bind();

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2; // working with 2 shaders here, vertex and fragment shaders
    static const unsigned int NUM_UNIFORMS = 3;

    Shader(const Shader &other) {}
    void operator=(const Shader &rhs) {}

    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMsg);
    std::string LoadShader(const std::string &fileName);
    GLuint CreateShader(const std::string &name, unsigned int type);

    GLuint m_program; // refer to shader program with opengl
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H