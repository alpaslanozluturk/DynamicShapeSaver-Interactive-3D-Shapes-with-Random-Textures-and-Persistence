#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace graf {
    class ShaderProgram {
    public:
        void create();
        void attachShader(const std::string& fileName, unsigned int shaderType);
        void link();
        void use();
        void addUniform(const std::string& varName);
        void setFloat(const std::string& varName, float value);
        void setVec4(const std::string& varName, const glm::vec4& value);
        void setVec3(const std::string& varName, const glm::vec3& value);
        void setMat4(const std::string& varName, const glm::mat4& value);
        void setInt(const std::string& varName, int value); // Yeni fonksiyon
    private:
        unsigned int m_id;
        std::unordered_map<std::string, int> m_uniforms;

        std::string getShaderFromFile(const std::string& fileName);
    };
}

#endif // SHADERPROGRAM_HPP
