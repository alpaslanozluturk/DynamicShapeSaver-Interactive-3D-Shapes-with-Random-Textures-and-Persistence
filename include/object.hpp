#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <string>
#include "vertexarrayobject.hpp"
#include "shapecreator.hpp"
#include "shapecreator.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.hpp"
#include "texturemanager.hpp"

class Object {
public:
    glm::vec3 position;
    float rotationAngle; // Dönüş açısı
    graf::ShapeTypes shapeType;
    graf::VertexArrayObject* vao;
    std::string textureName; // Texture dosya adı

    // Constructor
    Object(const glm::vec3& initialPosition, graf::ShapeTypes initialShape, const std::string& texture)
        : position(initialPosition), rotationAngle(0.0f), shapeType(initialShape), vao(nullptr), textureName(texture) {
        graf::ShapeCreator shapeCreator;
        vao = shapeCreator.create(shapeType); // İlk şekli oluştur
    }

    // Destructor
    ~Object() {
        if (vao) {
            vao->release();
            delete vao;
        }
    }

    // Şekil değiştirme
    void changeShape() {
        if (vao) {
            vao->release();
            delete vao;
            vao = nullptr; // Güvenlik için pointer'ı sıfırlıyoruz
        }
        shapeType = static_cast<graf::ShapeTypes>((static_cast<int>(shapeType) + 1) % 5);
        graf::ShapeCreator shapeCreator;
        vao = shapeCreator.create(shapeType);
    }

    // Çizim
    void draw(graf::ShaderProgram& program, const glm::mat4& mtxProj) {
        glm::mat4 mtxTranslate = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 mtxRotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mtxWorld = mtxTranslate * mtxRotate;

        program.setMat4("uWorldTransform", mtxProj * mtxWorld);

        // Texture bağlama
        graf::TextureManager::getInstance()->activateTexture(textureName);

        vao->bind();
        vao->draw();
    }
};

#endif // OBJECT_HPP