#ifndef MODEL_H
#define MODEL_H


#include <vector>
#include "shader.h"
#include "customgltemplates.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

class CModel
{
public:
	CModel();
	CModel(std::vector<GLfloat> vertices);
    const glm::vec3 getPosition() const;
    const glm::vec3 getEulers() const;
    void setPosition(glm::vec3 position, glm::vec3 eulers);
    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);
    void DrawModel(CShader& shader) const;
	size_t AddChild (CModel* child);
	void clearChilds();

private:
    glm::mat4 m_modelMatrix;
    glm::vec3 m_position;
    glm::vec3 m_eulers;
	std::vector<CModel*>m_childs;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_vertexCount;

	void RefreshMatrix ();
	void DrawModel (CShader& shader, glm::mat4 parent) const;
	bool hasParent = false;
};

#endif // MODEL_H
