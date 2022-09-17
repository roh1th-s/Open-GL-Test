#include <iostream>
#include <fstream>

#include "shader.h"

Shader::Shader(const std::string &filename)
{
    m_program = glCreateProgram(); 
    m_shaders[0] = CreateShader(LoadShader(filename + ".vs.glsl"), GL_VERTEX_SHADER);
    m_shaders[0] = CreateShader(LoadShader(filename + ".fs.glsl"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(m_program, m_shaders[i]);
    }

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

    m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

Shader::~Shader()
{   
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

std::string Shader::LoadShader(const std::string& fileName) {
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if(file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader : " << fileName << std::endl;
    }
    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << errorMsg << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& name, unsigned int type) {
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;
    
    const GLchar* sources[1];
    sources[0] = name.c_str();

    GLint sourceLengths[1];
    sourceLengths[0] = name.length();

    glShaderSource(shader, 1, sources, sourceLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}

