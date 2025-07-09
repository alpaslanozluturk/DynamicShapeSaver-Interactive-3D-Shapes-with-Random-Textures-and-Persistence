#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <unordered_map>

namespace graf {
    class TextureManager {
    public:
        static TextureManager* getInstance(); // Artık public
        void addTextureFromFile(const std::string& fileName);
        void activateTexture(const std::string& textureName);

    private:
        static TextureManager* m_Ins;
        std::unordered_map<std::string, unsigned int> m_textureMap;

        TextureManager();
    };
}

#endif // TEXTUREMANAGER_HPP
