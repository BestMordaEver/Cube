#ifndef CUSTOMGLTEMPLATES_H
#define CUSTOMGLTEMPLATES_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct SVertex
{
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_textureCoords;
};

#endif // CUSTOMGLTEMPLATES_H
