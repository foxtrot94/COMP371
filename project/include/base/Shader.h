#pragma once
#include <string>
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library

class Shader
{
private:
	std::string readShaderCodeFromFile(std::string shader_path);
	GLuint createShader(std::string shaderCode, GLenum shaderType);
	GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	GLuint createShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);

	GLuint shaderProgram;

	GLuint transformLoc;
	GLuint viewMatrixLoc;
	GLuint projectionLoc;

public:
	struct Uniforms {
		GLuint transformMatrixPtr;
		GLuint viewMatrixPtr;
		GLuint projectMatrixPtr;
		Uniforms() {
			transformMatrixPtr = NULL;
			viewMatrixPtr = NULL;
			projectMatrixPtr = NULL;
		}
	};

	Shader(std::string vertex_shader_path, std::string fragment_shader_path);
	~Shader();

	inline GLuint getShaderProgram() { return shaderProgram; };
	Uniforms getUniforms();
};

