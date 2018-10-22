#include "model.h"

CModel::CModel() {};
CModel::CModel(std::vector<GLfloat> vertices)
{
	m_vertexCount = vertices.size() * sizeof(GLfloat);

	glGenVertexArrays (1, &m_VAO);
	glGenBuffers (1, &m_VBO);

	glBindVertexArray (m_VAO);

	glBindBuffer (GL_ARRAY_BUFFER, m_VBO);
	glBufferData (GL_ARRAY_BUFFER, m_vertexCount, vertices.data(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray (0);
	// TexCoord attribute
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), (GLvoid*)(3 * sizeof (GLfloat)));
	glEnableVertexAttribArray (2);

	glBindVertexArray (0); // Unbind VAO

	RefreshMatrix ();
}

const glm::vec3 CModel::getPosition () const
{
	return m_eulers;
}

const glm::vec3 CModel::getEulers () const
{
	return m_position;
}

void CModel::setPosition (glm::vec3 position, glm::vec3 eulers)
{
	m_position = position;
	m_eulers = eulers;
	RefreshMatrix ();
}

void CModel::move (glm::vec3 direction)
{
	m_position += direction;
	RefreshMatrix ();
}

void CModel::rotate (glm::vec3 direction)
{
	m_eulers += direction;
	RefreshMatrix ();
}

void CModel::DrawModel (CShader& shader) const
{
	if (hasParent)
	{
		return;
	}
	GLuint modelLocation = glGetUniformLocation (shader.Program (), "model");
	glUniformMatrix4fv (modelLocation, 1, GL_FALSE, glm::value_ptr (m_modelMatrix));

	glBindVertexArray (m_VAO);
	glDrawArrays (GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray (0);
	for (const auto& child : m_childs)
	{
		child->DrawModel (shader, m_modelMatrix);
	}
}

void CModel::DrawModel (CShader& shader, glm::mat4 parent) const
{
	GLuint modelLocation = glGetUniformLocation (shader.Program (), "model");
	glUniformMatrix4fv (modelLocation, 1, GL_FALSE, glm::value_ptr (parent * m_modelMatrix));

	glBindVertexArray (m_VAO);
	glDrawArrays (GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray (0);
	for (const auto& child : m_childs)
	{
		child->DrawModel (shader, parent * m_modelMatrix);
	}
}

size_t CModel::AddChild (CModel* child)
{
	m_childs.emplace_back (std::move (child));
	m_childs.back()->m_modelMatrix *= glm::inverse(m_modelMatrix);
	m_childs.back()->hasParent = true;
	return m_childs.size () - 1;
}

void CModel::clearChilds()
{
	for (auto child : m_childs)
	{
		child->m_modelMatrix = m_modelMatrix * child->m_modelMatrix;
		child->hasParent = false;
	}
	m_childs.clear();
}

void CModel::RefreshMatrix ()
{
	m_modelMatrix = glm::mat4 ();
	m_modelMatrix = glm::rotate (m_modelMatrix, m_eulers.x, glm::vec3 (1, 0, 0));
	m_modelMatrix = glm::rotate (m_modelMatrix, m_eulers.y, glm::vec3 (0, 1, 0));
	m_modelMatrix = glm::rotate (m_modelMatrix, m_eulers.z, glm::vec3 (0, 0, 1));
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
}

