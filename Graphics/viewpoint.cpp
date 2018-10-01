#include "viewpoint.h"

static const GLfloat PI = glm::radians (180.f);

CViewPoint::CViewPoint (CShader&& shader, GLuint width, GLuint height) :
	m_shader (shader),
	m_width (width),
	m_height (height),
	m_clearColor (0.5f, 0.5f, 0.5f, 1),
	m_position (0, 0, 0),
	m_cameraDistance (1),
	m_projection (glm::perspective (glm::radians (45.f), (GLfloat)m_width / m_height, 0.1f, 100.f)),
	m_viewLocation (glGetUniformLocation (m_shader.Program (), "view")),
	m_projectionLocation (glGetUniformLocation (m_shader.Program (), "projection"))
{

}

void CViewPoint::SetCamera (glm::vec3 position, glm::vec3 eulers)
{
	m_position = position;
	m_eulers = eulers;
	refreshMatrixes ();
}

void CViewPoint::UseCamera ()
{
	m_shader.Use ();
	glUniformMatrix4fv (m_viewLocation, 1, GL_FALSE, glm::value_ptr (m_view));
	glUniformMatrix4fv (m_projectionLocation, 1, GL_FALSE, glm::value_ptr (m_projection));
	glClearColor (m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
}

void CViewPoint::drawModel (const CModel& target)
{
	target.DrawModel (m_shader);
}

void CViewPoint::move (glm::vec3 direction)
{
	m_position += direction;
	refreshMatrixes ();
}

void CViewPoint::rotate (glm::vec3 _eulers)
{
	m_eulers += _eulers;
	refreshMatrixes ();
}

glm::vec3 CViewPoint::getPosition ()
{
	return m_position;
}

glm::vec3 CViewPoint::getEulers ()
{
	return m_eulers;
}

void CViewPoint::refreshMatrixes ()
{
	while (m_eulers.x > 2 * PI)
	{
		m_eulers.x -= 2 * PI;
	}
	while (m_eulers.x < 0)
	{
		m_eulers.x += 2 * PI;
	}

	if (m_eulers.y > PI / 2 - 0.05f)
	{
		m_eulers.y = PI / 2 - 0.05f;
	}
	if (m_eulers.y < -PI / 2 + 0.05f)
	{
		m_eulers.y = -PI / 2 + 0.05f;
	}

	while (m_eulers.z > 2 * PI)
	{
		m_eulers.z -= 2 * PI;
	}
	while (m_eulers.z < 0)
	{
		m_eulers.z += 2 * PI;
	}

	glm::vec3 cameraTarget (-m_cameraDistance*glm::sin (m_eulers.x)*glm::cos (m_eulers.y),
		m_cameraDistance*glm::sin (m_eulers.y),
		m_cameraDistance*glm::cos (m_eulers.x)*glm::cos (m_eulers.y));

	m_view = glm::lookAt (m_position, m_position + cameraTarget, glm::vec3 (0, 1, 0));
}
