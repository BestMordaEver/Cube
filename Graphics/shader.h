#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

class CShader
{
public:
    // Constructor generates the shader on the fly
    CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Uses the current shader
    void Use();

	GLuint Program ();

private:
	GLuint m_program;
};

#endif

