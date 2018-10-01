#ifndef VIEWPOINT_H
#define VIEWPOINT_H

#include "shader.h"
#include "model.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>



class CViewPoint
{
public:
    CViewPoint(CShader&& shader, GLuint width, GLuint height);
    void SetCamera(glm::vec3 position, glm::vec3 eulers);
    void UseCamera();
    void drawModel (const CModel& target);
    void move(glm::vec3 direction);
    void rotate(glm::vec3 eulers);
    glm::vec3 getPosition();
    glm::vec3 getEulers();

private:
	GLuint m_width;
	GLuint m_height;
    CShader m_shader;
    GLuint m_viewLocation;
    GLuint m_projectionLocation;
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::vec4 m_clearColor;
    glm::vec3 m_position;
    glm::vec3 m_eulers;
    GLfloat m_cameraDistance;

    void refreshMatrixes();
};

#endif // VIEWPOINT_H
