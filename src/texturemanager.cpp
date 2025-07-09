#define STB_IMAGE_IMPLEMENTATION
#include "texturemanager.hpp"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

namespace graf {
    TextureManager* TextureManager::m_Ins = nullptr;

    TextureManager* TextureManager::getInstance() { // Artık erişilebilir
        if (m_Ins == nullptr) {
            m_Ins = new TextureManager();
        }
        return m_Ins;
    }

    void TextureManager::addTextureFromFile(const std::string& fileName) {
        if (m_textureMap.count(fileName) > 0) {
            std::cerr << "Texture already loaded: " << fileName << std::endl;
            return;
        }

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            std::cerr << "Failed to load texture: " << fileName << std::endl;
            return;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        m_textureMap[fileName] = texture;
        std::cerr << "Texture loaded and assigned: " << fileName << ", ID: " << texture << std::endl;
    }

    void TextureManager::activateTexture(const std::string& textureName) {
        if (m_textureMap.count(textureName) == 0) {
            std::cerr << "Texture not found: " << textureName << std::endl;
            return;
        }

        glBindTexture(GL_TEXTURE_2D, m_textureMap[textureName]);
    }

    TextureManager::TextureManager() {}
}
