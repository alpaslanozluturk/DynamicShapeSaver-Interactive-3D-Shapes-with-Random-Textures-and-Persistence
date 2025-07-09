#include "shaderprogram.hpp"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace graf {
    void ShaderProgram::create() {
        m_id = glCreateProgram();
    }

    void ShaderProgram::link() {
        glLinkProgram(m_id);
    }

    void ShaderProgram::use() {
        glUseProgram(m_id);
    }

    void ShaderProgram::attachShader(const string& fileName, unsigned int shaderType) {
        unsigned int shaderId = glCreateShader(shaderType);
        string source = getShaderFromFile(fileName);

        const char* sourceTemp = &source[0];
        glShaderSource(shaderId, 1, &sourceTemp, NULL);
        glCompileShader(shaderId);

        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
            cerr << "Shader Compilation Error: " << &errorLog[0] << endl;

            glDeleteShader(shaderId);
            return;
        }

        glAttachShader(m_id, shaderId);
    }

    string ShaderProgram::getShaderFromFile(const string& fileName) {
        ifstream file(fileName);
        string data;

        if (file.is_open()) {
            char readChar;
            while ((readChar = file.get()) != EOF) {
                data += readChar;
            }
            file.close();
        }

        return data;
    }

    void ShaderProgram::addUniform(const string& varName) {
        m_uniforms[varName] = glGetUniformLocation(m_id, varName.c_str());
    }

    void ShaderProgram::setFloat(const string& varName, float value) {
        if (m_uniforms.count(varName) > 0) {
            unsigned int varLocation = m_uniforms[varName];
            glUniform1f(varLocation, value);
        }
    }

    void ShaderProgram::setVec4(const string& varName, const glm::vec4& value) {
        if (m_uniforms.count(varName) > 0) {
            unsigned int varLocation = m_uniforms[varName];
            glUniform4f(varLocation, value.r, value.g, value.b, value.a);
        }
    }

    void ShaderProgram::setVec3(const string& varName, const glm::vec3& value) {
        if (m_uniforms.count(varName) > 0) {
            unsigned int varLocation = m_uniforms[varName];
            glUniform3f(varLocation, value.x, value.y, value.z);
        }
    }

    void ShaderProgram::setMat4(const string& varName, const glm::mat4& value) {
        if (m_uniforms.count(varName) > 0) {
            unsigned int varLocation = m_uniforms[varName];
            glUniformMatrix4fv(varLocation, 1, GL_FALSE, &value[0][0]);
        }
    }

    void ShaderProgram::setInt(const string& varName, int value) { // Yeni fonksiyon
        if (m_uniforms.count(varName) > 0) {
            unsigned int varLocation = m_uniforms[varName];
            glUniform1i(varLocation, value);
        }
    }
}
