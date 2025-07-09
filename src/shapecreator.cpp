#include "shapecreator.hpp"
#include "vertexarrayobject.hpp"
#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"
#include "vertextypes.hpp"

namespace graf
{
    VertexArrayObject* ShapeCreator::create(ShapeTypes shape)
    {
        switch (shape)
        {
        case ShapeTypes::Square:           return createSquare();
            
        case ShapeTypes::Circle:           return createCircle(10);
            
        case ShapeTypes::Cube:             return createCube();

        case ShapeTypes::Pyramid:          return createPyramid();

        case ShapeTypes::Frustum:          return createFrustum();
        default:
            return nullptr;
            break;
        }
    }
    VertexArrayObject* ShapeCreator::createCircle(int anglesInDegrees)
    {

        if(m_vaoMap.count(ShapeTypes::Circle)>0)
            return m_vaoMap[ShapeTypes::Circle];

        graf::VertexArrayObject *   va = new VertexArrayObject();
        graf::VertexBuffer*         vb = new VertexBuffer();
        graf::IndexBuffer*          ib = new IndexBuffer();
       
        int vertexCount = 360/anglesInDegrees;
        int faceCount = vertexCount-2;

        VertexList vertices;
        IndexList indices;       
        
        for(int i=0;i<vertexCount;i++)
        {
            Vertex vertex;
            
            double currentAngle =anglesInDegrees*i;
            vertex.position.x= glm::cos(glm::radians(currentAngle));
            vertex.position.y = glm::sin(glm::radians(currentAngle));
            vertex.position.z = 0.0f;
            vertex.texture.s = 0.5+0.5*glm::cos(glm::radians(currentAngle));
            vertex.texture.t = 0.5+0.5*glm::sin(glm::radians(currentAngle));
            vertices.emplace_back(vertex);
           
        }
        for(int i=0;i<faceCount;i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(i+2);
            indices.emplace_back(i+1);
        }
        va->create();
        vb->create(&vertices[0],sizeof(Vertex)*vertices.size());      
        ib->create(&indices[0],sizeof(unsigned int)*indices.size());
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(graf::VertexAttributeType::Position);
        va->addVertexAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        va->unbind();
        vb->unbind();
        ib->unbind();

        m_vaoMap[ShapeTypes::Circle]= va;
        return va;
    }
VertexArrayObject* ShapeCreator::createSquare() {
    if (m_vaoMap.count(ShapeTypes::Square) > 0)
        return m_vaoMap[ShapeTypes::Square];

    // Vertexler (köşe pozisyonları ve texture koordinatları)
    float vertices[] = {
        //   x     y     z     s    t
        -0.5f,  0.5f, -1.0f,  0.0f, 1.0f,  // Sol üst
         0.5f,  0.5f, -1.0f,  1.0f, 1.0f,  // Sağ üst
         0.5f, -0.5f, -1.0f,  1.0f, 0.0f,  // Sağ alt
        -0.5f, -0.5f, -1.0f,  0.0f, 0.0f   // Sol alt
    };

    // Indices (üçgenlerin tanımı)
    unsigned int indices[] = {
        0, 1, 2,  // Üst üçgen
        2, 3, 0   // Alt üçgen
    };

    // VAO, VBO ve IBO oluşturma
    VertexArrayObject* va = new VertexArrayObject();
    VertexBuffer* vb = new VertexBuffer();
    IndexBuffer* ib = new IndexBuffer();

    vb->create(vertices, sizeof(vertices)); // Vertex verisi yükleme
    ib->create(indices, sizeof(indices));   // Index verisi yükleme
    va->create();

    va->setVertexBuffer(vb);
    va->setIndexBuffer(ib);

    // Pozisyon ve texture koordinatları için attribute ekleme
    va->addVertexAttribute(VertexAttributeType::Position);
    va->addVertexAttribute(VertexAttributeType::Texture);

    va->activateAttributes();

    // Bağlantıları kapatma
    va->unbind();
    vb->unbind();
    ib->unbind();

    m_vaoMap[ShapeTypes::Square] = va;

    return va;
}

    VertexArrayObject* ShapeCreator::createCube()
    {
        if(m_vaoMap.count(ShapeTypes::Cube)>0)
            return m_vaoMap[ShapeTypes::Cube];

        glm::vec3 positions[] = {  
            {-0.5f,  0.5f, 0.5f},
            { 0.5f,  0.5f, 0.5f},
            { 0.5f, -0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},

            {-0.5f, 0.5f, -0.5f},
            {0.5f,  0.5f,  -0.5f},
            {0.5f, -0.5f, -0.5f},
            {-0.5f,-0.5f,-0.5f}        
        }; 


        int vertexCount = 24;
        Vertex* vertices= new Vertex[vertexCount];
        std::vector<unsigned int> indices;


        //Ön Yüz
        vertices[0].position = positions[0];
        vertices[1].position = positions[1];
        vertices[2].position = positions[2];
        vertices[3].position = positions[3];

        vertices[0].texture = glm::vec2(0.0f,1.0f);
        vertices[1].texture = glm::vec2(1.0f,1.0f);
        vertices[2].texture = glm::vec2(1.0f,0.0f);
        vertices[3].texture = glm::vec2(0.0f,0.0f);


        //Sağ Yüz
        vertices[4].position = positions[1];
        vertices[5].position = positions[5];
        vertices[6].position = positions[6];
        vertices[7].position = positions[2];

        vertices[4].texture = glm::vec2(0.0f,1.0f);
        vertices[5].texture = glm::vec2(1.0f,1.0f);
        vertices[6].texture = glm::vec2(1.0f,0.0f);
        vertices[7].texture = glm::vec2(0.0f,0.0f);



        //Üst Yüz
        vertices[8].position = positions[4];
        vertices[9].position = positions[5];
        vertices[10].position = positions[1];
        vertices[11].position = positions[0];

        vertices[8].texture = glm::vec2(0.0f,1.0f);
        vertices[9].texture = glm::vec2(1.0f,1.0f);
        vertices[10].texture = glm::vec2(1.0f,0.0f);
        vertices[11].texture = glm::vec2(0.0f,0.0f);

        //Sol Yüz
        vertices[12].position = positions[4];
        vertices[13].position = positions[0];
        vertices[14].position = positions[3];
        vertices[15].position = positions[7];

        vertices[12].texture = glm::vec2(0.0f,1.0f);
        vertices[13].texture = glm::vec2(1.0f,1.0f);
        vertices[14].texture = glm::vec2(1.0f,0.0f);
        vertices[15].texture = glm::vec2(0.0f,0.0f);

        //Arka Yüz
        vertices[16].position = positions[5];
        vertices[17].position = positions[4];
        vertices[18].position = positions[7];
        vertices[19].position = positions[6];

        vertices[16].texture = glm::vec2(0.0f,1.0f);
        vertices[17].texture = glm::vec2(1.0f,1.0f);
        vertices[18].texture = glm::vec2(1.0f,0.0f);
        vertices[19].texture = glm::vec2(0.0f,0.0f);

        //Alt Yüz
        vertices[20].position = positions[3];
        vertices[21].position = positions[2];
        vertices[22].position = positions[6];
        vertices[23].position = positions[7];

        vertices[20].texture = glm::vec2(0.0f,1.0f);
        vertices[21].texture = glm::vec2(1.0f,1.0f);
        vertices[22].texture = glm::vec2(1.0f,0.0f);
        vertices[23].texture = glm::vec2(0.0f,0.0f);
        for(int i=0;i<6;i++)
        {
            indices.push_back(i*4);
            indices.push_back(i*4+2);
            indices.push_back(i*4+1);

            indices.push_back(i*4);
            indices.push_back(i*4+3);
            indices.push_back(i*4+2);            
        }

        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb= new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices,sizeof(Vertex)*vertexCount);
        ib->create(indices.data(),indices.size()*sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();

        va->unbind();
        vb->unbind();
        ib->unbind();

        m_vaoMap[ShapeTypes::Cube] =va;

        return va;        
    }
    VertexArrayObject* ShapeCreator::createPyramid()
    {
        if (m_vaoMap.count(ShapeTypes::Pyramid) > 0)
            return m_vaoMap[ShapeTypes::Pyramid];

        // Piramidin vertex verileri
        glm::vec3 positions[] = {
            { 0.0f,  0.5f,  0.0f}, // Tepe noktası
            {-0.5f, -0.5f,  0.5f}, // Ön sol
            { 0.5f, -0.5f,  0.5f}, // Ön sağ
            { 0.5f, -0.5f, -0.5f}, // Arka sağ
            {-0.5f, -0.5f, -0.5f}  // Arka sol
        };

        VertexList vertices;
        IndexList indices;

        // Tepe yüzey
        vertices.push_back({ positions[0], {0.5f, 1.0f} });
        vertices.push_back({ positions[1], {0.0f, 0.0f} });
        vertices.push_back({ positions[2], {1.0f, 0.0f} });

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        // Sağ yüzey
        vertices.push_back({ positions[0], {0.5f, 1.0f} });
        vertices.push_back({ positions[2], {0.0f, 0.0f} });
        vertices.push_back({ positions[3], {1.0f, 0.0f} });

        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(5);

        // Arka yüzey
        vertices.push_back({ positions[0], {0.5f, 1.0f} });
        vertices.push_back({ positions[3], {0.0f, 0.0f} });
        vertices.push_back({ positions[4], {1.0f, 0.0f} });

        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(8);

        // Sol yüzey
        vertices.push_back({ positions[0], {0.5f, 1.0f} });
        vertices.push_back({ positions[4], {0.0f, 0.0f} });
        vertices.push_back({ positions[1], {1.0f, 0.0f} });

        indices.push_back(9);
        indices.push_back(10);
        indices.push_back(11);

        // Alt taban
        vertices.push_back({ positions[1], {0.0f, 0.0f} });
        vertices.push_back({ positions[2], {1.0f, 0.0f} });
        vertices.push_back({ positions[3], {1.0f, 1.0f} });
        vertices.push_back({ positions[4], {0.0f, 1.0f} });

        indices.push_back(12);
        indices.push_back(13);
        indices.push_back(14);
        indices.push_back(12);
        indices.push_back(14);
        indices.push_back(15);

        VertexArrayObject* va = new VertexArrayObject();
        VertexBuffer* vb = new VertexBuffer();
        IndexBuffer* ib = new IndexBuffer();

        va->create();
        vb->create(&vertices[0], sizeof(Vertex) * vertices.size());
        ib->create(&indices[0], sizeof(unsigned int) * indices.size());
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(graf::VertexAttributeType::Position);
        va->addVertexAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        va->unbind();
        vb->unbind();
        ib->unbind();

        m_vaoMap[ShapeTypes::Pyramid] = va;
        return va;
    }
    VertexArrayObject* ShapeCreator::createFrustum() {
    if (m_vaoMap.count(ShapeTypes::Frustum) > 0)
        return m_vaoMap[ShapeTypes::Frustum];

    graf::VertexArrayObject* va = new VertexArrayObject();
    graf::VertexBuffer* vb = new VertexBuffer();
    graf::IndexBuffer* ib = new IndexBuffer();

    VertexList vertices;
    IndexList indices;

    // Küplerin alt yüzey y koordinatı
    float cubeBottomY = -0.5f; // Küpün alt yüzeyi
    float cubeTopY = 0.5f;    // Küpün üst yüzeyi

    // Küpün kenar uzunluğu ve alt yüzey alanı
    float cubeSideLength = 1.0f; // Küpün kenar uzunluğu 
    float cubeArea = cubeSideLength * cubeSideLength;

    // Frustum özellikleri
    float bottomSize = cubeSideLength / 2.0f; 
    float topSize = (bottomSize / 2.0f) * sqrt(0.85f); 

    // Frustum'un alt ve üst yüzey y koordinatları
    float bottomHeight = cubeBottomY;  
    float topHeight = cubeTopY;        

    // Alt taban köşeleri
    vertices.push_back({{-bottomSize, bottomHeight, -bottomSize}, {0.0f, 0.0f}});
    vertices.push_back({{ bottomSize, bottomHeight, -bottomSize}, {1.0f, 0.0f}});
    vertices.push_back({{ bottomSize, bottomHeight,  bottomSize}, {1.0f, 1.0f}});
    vertices.push_back({{-bottomSize, bottomHeight,  bottomSize}, {0.0f, 1.0f}});

    // Üst taban köşeleri 
    vertices.push_back({{-topSize, topHeight, -topSize}, {0.25f, 0.25f}});
    vertices.push_back({{ topSize, topHeight, -topSize}, {0.75f, 0.25f}});
    vertices.push_back({{ topSize, topHeight,  topSize}, {0.75f, 0.75f}});
    vertices.push_back({{-topSize, topHeight,  topSize}, {0.25f, 0.75f}});

    // Yan yüzeyler için texture koordinatları
    float sideTexCoordX = 0.5f;
    vertices.push_back({{-bottomSize, bottomHeight, -bottomSize}, {0.0f, 0.0f}});
    vertices.push_back({{ bottomSize, bottomHeight, -bottomSize}, {1.0f, 0.0f}});
    vertices.push_back({{ topSize, topHeight, -topSize}, {0.5f, 1.0f}});
    vertices.push_back({{-topSize, topHeight, -topSize}, {0.0f, 1.0f}});

    // Alt taban için yüzey
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    // Üst taban için yüzey
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);

    // Yan yüzeyler
    for (int i = 0; i < 4; ++i) {
        indices.push_back(i);
        indices.push_back((i + 1) % 4);
        indices.push_back(4 + i);

        indices.push_back((i + 1) % 4);
        indices.push_back(4 + ((i + 1) % 4));
        indices.push_back(4 + i);
    }

    va->create();
    vb->create(&vertices[0], sizeof(Vertex) * vertices.size());
    ib->create(&indices[0], sizeof(unsigned int) * indices.size());
    va->setVertexBuffer(vb);
    va->setIndexBuffer(ib);
    va->addVertexAttribute(graf::VertexAttributeType::Position);
    va->addVertexAttribute(graf::VertexAttributeType::Texture);
    va->activateAttributes();

    va->unbind();
    vb->unbind();
    ib->unbind();

    m_vaoMap[ShapeTypes::Frustum] = va;
    return va;
}


}