#include "vertexarrayobject.hpp"
#include "shapecreator.hpp"
#include "object.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream> // Debug için kullanılabilir

Object::Object(const glm::vec3& initialPosition, graf::ShapeTypes initialShape, const std::string& texture)
    : position(initialPosition), rotationAngle(0.0f), shapeType(initialShape), vao(nullptr), textureName(texture) {
    graf::ShapeCreator shapeCreator;
    vao = shapeCreator.create(shapeType); // İlk şekli oluştur
}

Object::~Object() {
    if (vao) {
        vao->release();
        delete vao;
    }
}

void Object::changeShape() {
    if (vao) {
        vao->release();
        delete vao;
        vao = nullptr; // Güvenlik için pointer'ı sıfırlıyoruz
    }
    shapeType = static_cast<graf::ShapeTypes>((static_cast<int>(shapeType) + 1) % 4); // 4 farklı şekil
    graf::ShapeCreator shapeCreator;
    vao = shapeCreator.create(shapeType);
}

void Object::draw(graf::ShaderProgram& program, const glm::mat4& mtxProj) {
    glm::mat4 mtxTranslate = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 mtxRotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mtxScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f)); // Ölçekleme oranı küçültüldü
    glm::mat4 mtxWorld = mtxTranslate * mtxRotate * mtxScale;

    program.setMat4("uWorldTransform", mtxProj * mtxWorld);

    graf::TextureManager::getInstance()->activateTexture(textureName);

    vao->bind();
    vao->draw();
}