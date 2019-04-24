//
// Created by Marian Cichy
//

#include "Shader.h"
#include <fstream>
#include <iostream>
#include <ext.hpp>

using namespace std;

namespace mrn {
    const char *Shader::readFile(const char *filepath) {
        size_t size = 0;
        char *contents = nullptr;
        ifstream file(filepath, ios::in | ios::binary | ios::ate);

        if (!file.is_open()) {
            cout << "Error reading file:" << filepath << std::endl;
            return nullptr;
        }

        file.seekg(0, ios::end);
        size = (size_t) file.tellg();
        contents = new char[size + 1];
        contents[size] = '\0';
        file.seekg(0, ios::beg);
        file.read(contents, size);
        file.close();
        return contents;
    }

    Shader::Shader(const char *vertexPath, const char *fragmentPath) {
        int shaderCompileSuccess;
        char infoLog[512];

        // reading and compiling vertex Shader
        const char *vertexSource = Shader::readFile(vertexPath);
        GLuint vertexShaderId;
        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexSource, nullptr);
        glCompileShader(vertexShaderId);
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
        if (!shaderCompileSuccess) {
            glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            memset(infoLog, 0, 512);
        }

        // reading and compiling fragment Shader
        const char *fragmentSource = Shader::readFile(fragmentPath);
        GLuint fragmentShaderId;
        fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShaderId);
        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
        if (!shaderCompileSuccess) {
            glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            memset(infoLog, 0, 512);
        }
        // link vertex and fragment shader
        GLint shaderLinkSuccess;
        this->id = glCreateProgram();
        glAttachShader(this->id, vertexShaderId);
        glAttachShader(this->id, fragmentShaderId);
        glLinkProgram(this->id);
        glGetProgramiv(this->id, GL_LINK_STATUS, &shaderLinkSuccess);

        if (!shaderLinkSuccess) {
            glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

    }

    void Shader::use() {
        glUseProgram(this->id);
    }

    void Shader::translate() {
        GLint proj_loc = glGetUniformLocation(id, "projection");
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
    }
}