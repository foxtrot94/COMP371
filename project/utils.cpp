#include <iostream>
#include <fstream>
#include <vector>
#include "..\glew\glew.h"
#include "utils.h"

//Checks if a file is on disk and is readable
bool FileExists(std::string filename)
{
	std::ifstream test(filename);
	bool status = test.is_open() && test.good();
	test.close();
	return status;
}

bool AppInit(std::string windowName, const unsigned int minHeight, const unsigned int minWidth, GLFWwindow** outWindow)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	*outWindow = glfwCreateWindow(minWidth, minHeight, windowName.c_str(), nullptr, nullptr);
	if (outWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(*outWindow);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	//Good to go.
	return true;
}

GLuint OpenAndCompile(std::string filename, GLuint GLShaderType)
{
	if (!FileExists(filename)) {
		std::cout << "Given filename " << filename << " for shader source does not exist. Skipping Compilation." << std::endl;
		return NULL;
	}

	std::ifstream shaderSourceFile;
	std::string lineBuffer, shaderSource;
	shaderSourceFile.open(filename);
	if (shaderSourceFile.is_open()){
		while (getline(shaderSourceFile, lineBuffer)) {
			shaderSource += lineBuffer + '\n';
		}
		shaderSourceFile.close();
	}
	else {
		std::cout << "Given filename " << filename << " for shader source is inaccessible. Skipping Compilation" << std::endl;
		return NULL;
	}

	char const * shaderSrcPtr = shaderSource.c_str();

	GLuint shader = glCreateShader(GLShaderType);
	glShaderSource(shader, 1, &shaderSrcPtr, NULL);
	glCompileShader(shader);

	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << "Shader compilation error! Check log below" << std::endl;
		std::cout << log << std::endl;
	}
	return shader;
}

GLuint UseShaders(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	int success = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		char log[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED"<< std::endl;
		std::cout << log << std::endl;
	}

	//delete the used shaders and free up memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
	return shaderProgram;
}

