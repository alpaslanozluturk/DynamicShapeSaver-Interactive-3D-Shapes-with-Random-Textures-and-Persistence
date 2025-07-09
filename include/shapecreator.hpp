#ifndef shapecreator_hpp
#define shapecreator_hpp
#include<unordered_map>
#include "vertexarrayobject.hpp"
#include<glm/glm.hpp>
#include <map>
namespace graf
{
    enum class ShapeTypes
    {
        Cube,
        Circle,
        Square,
        Pyramid,
        Frustum
    };

    class ShapeCreator
    {
    public:
        VertexArrayObject* create(ShapeTypes shape);

    private:
        std::map<ShapeTypes, VertexArrayObject*> m_vaoMap;

        VertexArrayObject* createCube();
        VertexArrayObject* createCircle(int anglesInDegrees);
        VertexArrayObject* createSquare();
        VertexArrayObject* createPyramid(); 
        VertexArrayObject* createFrustum(); 
    };
}

#endif // SHAPECREATOR_HPP