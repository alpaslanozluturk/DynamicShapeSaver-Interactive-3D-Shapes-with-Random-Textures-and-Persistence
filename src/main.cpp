#define GLFW_INCLUDE_NONE
#include "GLWindow.hpp"
#include "shaderprogram.hpp"
#include "texturemanager.hpp"
#include "object.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int activeObjectIndex = -1;
vector<Object*> objects;

// Objeleri TXT dosyasına kaydetme fonksiyonu
void saveObjectsToFile(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Dosya açılamadı: " << fileName << endl;
        return;
    }

    for (const auto& obj : objects) {
        file << obj->position.x << " " << obj->position.y << " " << obj->position.z << " "
             << obj->rotationAngle << " "
             << static_cast<int>(obj->shapeType) << " "
             << obj->textureName << "\n";
    }

    file.close();
    cout << "Objeler kaydedildi: " << fileName << endl;
}

// Objeleri TXT dosyasından yükleme fonksiyonu
vector<Object*> loadObjectsFromFile(const string& fileName) {
    ifstream file(fileName);
    vector<Object*> loadedObjects;

    if (!file.is_open()) {
        cerr << "Dosya açılamadı veya bulunamadı: " << fileName << endl;
        return loadedObjects;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        glm::vec3 position;
        float rotationAngle;
        int shapeType;
        string textureName;

        ss >> position.x >> position.y >> position.z
           >> rotationAngle >> shapeType >> textureName;

        Object* obj = new Object(position, static_cast<graf::ShapeTypes>(shapeType), textureName);
        obj->rotationAngle = rotationAngle;

        // Objeyi tekrar bağlama ve çözme
        if (obj->vao) {
            obj->vao->bind();
            obj->vao->unbind();
        }

        loadedObjects.push_back(obj);
    }

    file.close();
    cout << "Objeler yüklendi: " << fileName << endl;
    return loadedObjects;
}

// Klavye işlevleri
void keyboardFunction(int key, int scancode, int action) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key >= GLFW_KEY_0 && key <= GLFW_KEY_8) {
            activeObjectIndex = key - GLFW_KEY_0;
            cout << "Aktif Obje: " << activeObjectIndex << endl;
        }

        if (activeObjectIndex != -1) {
            Object* activeObject = objects[activeObjectIndex];
            if (key == GLFW_KEY_UP) {
                activeObject->position.y += 0.1f;
            }
            if (key == GLFW_KEY_DOWN) {
                activeObject->position.y -= 0.1f;
            }
            if (key == GLFW_KEY_LEFT) {
                activeObject->position.x -= 0.1f;
            }
            if (key == GLFW_KEY_RIGHT) {
                activeObject->position.x += 0.1f;
            }
        }

        if (key == GLFW_KEY_SPACE && activeObjectIndex != -1) {
            objects[activeObjectIndex]->changeShape();
            cout << "Obje " << activeObjectIndex << " yeni şekle geçti." << endl;
        }
    }
}

int main(int argc, char** argv) {
    graf::GLWindow glwindow;
    if (glwindow.create(800, 800) < 0) {
        cerr << "Failed to create GL window." << endl;
        return -1;
    }

    glwindow.setKeyboardFunction(keyboardFunction);

    graf::ShaderProgram program;
    program.create();
    program.attachShader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
    program.attachShader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uWorldTransform");
    program.addUniform("texture1");

    // Texture birimini bağlama
    glActiveTexture(GL_TEXTURE0);
    program.setInt("texture1", 0);

    // Texture dosyalarını tanımlıyoruz
    vector<string> textures = {
        "./images/container.jpg",
        "./images/container2.jpg",
        "./images/container3.jpg",
        "./images/container4.jpg"
    };

    for (const auto& texture : textures) {
        graf::TextureManager::getInstance()->addTextureFromFile(texture);
    }

    // Objeleri TXT dosyasından yükleme
    string saveFileName = "objects_save.txt";
    objects = loadObjectsFromFile(saveFileName);

    // Eğer dosyadan yükleme başarısız olursa varsayılan objeleri oluştur
    if (objects.empty()) {
        vector<glm::vec3> positions = {
            {-2.5f,  2.5f, -6.5f}, { 0.0f,  2.5f, -6.5f}, { 2.5f,  2.5f, -6.5f},
            {-2.5f,  0.0f, -6.5f}, { 0.0f,  0.0f, -6.5f}, { 2.5f,  0.0f, -6.5f},
            {-2.5f, -2.5f, -6.5f}, { 0.0f, -2.5f, -6.5f}, { 2.5f, -2.5f, -6.5f}
        };

        for (size_t i = 0; i < positions.size(); ++i) {
            string texture = textures[i % textures.size()];
            objects.push_back(new Object(positions[i], graf::ShapeTypes::Cube, texture));
        }
    }

    // Perspektif matrisini güncelliyoruz
    glm::mat4 mtxProj = glm::perspective(glm::radians(75.0f), 1.0f, 1.0f, 30.0f);

    glwindow.setRenderFunction([&]() {
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();

        for (size_t i = 0; i < objects.size(); ++i) {
            if (static_cast<int>(i) == activeObjectIndex) {
                objects[i]->rotationAngle += 1.0f; // Sadece aktif obje dönsün
            }

            objects[i]->draw(program, mtxProj);
        }
    });

    glwindow.render();

    // Program sonlanırken objeleri TXT dosyasına kaydet
    saveObjectsToFile(saveFileName);

    // Belleği temizle
    for (auto& object : objects) {
        delete object;
    }

    return 0;
}
