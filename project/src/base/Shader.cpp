#include <fstream>
#include <iostream>

#include "base\Shader.h"

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
{
	//RIIA
	shaderProgram = NULL;

	//Create the Shader
	shaderProgram = createShaderProgram(vertex_shader_path, fragment_shader_path);
	//Get the location of uniforms in the shader
	transformLoc = glGetUniformLocation(shaderProgram, "model");
	viewMatrixLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	//Signal an issue if the loaded shader is malformed
	if (transformLoc == -1 || viewMatrixLoc == -1 || projectionLoc == -1) {
		std::cerr << "ERROR: the given shader does not have the expected uniforms" << std::endl;
		std::cerr << "Check that the name corresponds to what is used in the constructor" << std::endl;
		#if _DEBUG
			//Made this debug break to avoid debugging GLSL shaders. Check them to see what's wrong
			__debugbreak();
		#endif
	}
}

Shader::~Shader()
{

}

Shader::Uniforms Shader::getUniforms()
{
	if (shaderProgram == NULL) {
		return Uniforms();
	}
	
	Uniforms retVal;
	retVal.transformMatrixPtr = transformLoc;
	retVal.viewMatrixPtr = viewMatrixLoc;
	retVal.projectMatrixPtr = projectionLoc;

	return retVal;
}

// reads ShaderCode from a file (i.e. vertex.shader, fragment.shader) and returns the code as a string
std::string Shader::readShaderCodeFromFile(std::string shader_path)
{
	std::string ShaderCode;

	std::ifstream ShaderStream(shader_path, std::ios::in);

	if (ShaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", shader_path.c_str());
		#if _DEBUG
		//Made this debug break to avoid debugging GLSL shaders. Check them to see what's wrong
		__debugbreak();
		#endif
		exit(-1);
	}

	return ShaderCode;
}

// creates and returns a pointer to a shader created from shader code (received as parameter). The shaderType must be mentioned as GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
GLuint Shader::createShader(std::string shaderCode, GLenum shaderType)
{
	GLuint shader;

	shader = glCreateShader(shaderType);

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shader, 1, &sourcePointer, NULL);
	glCompileShader(shader);

	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (shaderType == GL_VERTEX_SHADER) {
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else if (shaderType == GL_FRAGMENT_SHADER) {
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	return shader;
}

// creates, links and returns a shader program, from a vertex shader and a fragment shader
GLuint Shader::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	return shaderProgram;

}

// creates a comp
GLuint Shader::createShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path)
{
	// ****************************************
	// * Build and compile our shader program *
	// ****************************************

	// Read Shaders from File
	std::string VertexShaderCode = readShaderCodeFromFile(vertex_shader_path);
	std::string FragmentShaderCode = readShaderCodeFromFile(fragment_shader_path);

	// Create/Compile Shaders 
	GLuint vertexShader = createShader(VertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(FragmentShaderCode, GL_FRAGMENT_SHADER);

	// Link shaders. Created shaderProgram
	GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

	return shaderProgram;
}
