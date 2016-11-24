#include "base\Renderer.h"
#include "base\Objects.h"
#include "base\Shader.h"
#include "objloader.hpp"

Renderer* Renderer::singleton = NULL;

Renderer::Renderer()
{
	mainWindow = NULL;
	shader = NULL;
}

Renderer::~Renderer()
{
	//Clear the context objects
	for (uint i = 0; i < ContextArrays.size(); ++i) {
		glDeleteVertexArrays(1, &(ContextArrays[i]));
	}
	ContextArrays.clear();

	for (uint i = 0; i < ContextBuffers.size(); ++i) {
		glDeleteBuffers(1, &(ContextBuffers[i]));
	}
	ContextBuffers.clear();

	delete shader; //this might cause some problems in the future
	delete skyBoxShader;

	singleton = NULL;
}

Renderer::Window* Renderer::Initialize(std::string windowName, const uint minWidth, const uint minHeight)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *outWindow = glfwCreateWindow(minWidth, minHeight, windowName.c_str(), nullptr, nullptr);
	if (outWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(outWindow);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return nullptr;
	}

	//Aditional features enabled by default
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	//Good to go.
	return new Window(outWindow,minWidth,minHeight,windowName);
}

Renderer::Window * Renderer::GetMainWindow()
{
	return mainWindow;
}

void Renderer::UseShader(Shader * shader)
{
	this->shader = shader;
	if (shader != NULL) {
		glUseProgram(shader->getShaderProgram());
	}
}

void Renderer::UseSkyBoxShader(Shader * shader)
{
	this->skyBoxShader = shader;
}

void Renderer::UpdateCamera(mat4 & view, mat4 & projection)
{
	if (shader == NULL) {
		return;
	}
	Shader::Uniforms uniforms = shader->getUniforms();

	glUniformMatrix4fv(uniforms.viewMatrixPtr, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms.projectMatrixPtr, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::Render(WorldGenericObject* Object)
{
	GLMesh* mesh = Object->getMesh();
	if (shader==NULL || mesh==NULL || !mesh->isInitialized()) {
		//nothing to do here
		return;
	}

	if (!mesh->isInRenderingContext()) {
		//Send it off to the GPU Video Memory
		//FUTURE: Right now all meshes are taken as static, change some day...
		AddToRenderingContext(mesh);
	}

	Shader::Uniforms uniform = shader->getUniforms(); //TODO: optimize in the future. Get uniforms outside or something
	glUniformMatrix4fv(uniform.transformMatrixPtr, 1, GL_FALSE, glm::value_ptr(*(Object->getModel())));

	glBindVertexArray(mesh->getContextArray());
	//Basically, draw RenderTarget
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, mesh->getBufferSize(), GL_UNSIGNED_INT, 0);//TODO?
	
	glBindVertexArray(0); //TODO: Optimize. Put this outside
}

void Renderer::Render(std::vector<WorldGenericObject*> Objects)
{
	glBindVertexArray(NULL);
	for (WorldGenericObject* object : Objects) {
		Render(object);
	}
	glBindVertexArray(NULL);
}

void Renderer::RenderSkyBox() {
	glUseProgram(skyBoxShader->getShaderProgram());
	glm::mat4 skybox_view = glm::mat4(1.f); // TODO set it to whatever updateCamera has

	Shader::Uniforms uniform = skyBoxShader->getUniforms();
	
	glUniformMatrix4fv(shader->getUniforms().viewMatrixPtr, 1, GL_FALSE, glm::value_ptr(skybox_view));

	glUniformMatrix4fv(skyBoxShader->getUniforms().viewMatrixPtr, 1, GL_FALSE, glm::value_ptr(skybox_view));
	
	glm::mat4 projection_matrix = glm::perspective(45.0f, (GLfloat)this->GetMainWindow()->width / (GLfloat)this->GetMainWindow()->height, 0.1f, 100.0f);
	glUniformMatrix4fv(skyBoxShader->getUniforms().projectMatrixPtr, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(glGetUniformLocation(skyboxShaderProgram, "skyboxTexture"), 1); //use texture unit 1

	glDepthMask(GL_FALSE);

	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, skybox_vertices.size());
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

bool Renderer::AddToRenderingContext(GLMesh * mesh)
{
	uint VAO, colorBO, vertexBO;
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &vertexBO);
	glGenBuffers(1, &colorBO);

	//synthesize the mesh data since it's been stored as a vec3
	std::vector<vec3> vertices = mesh->readLocalVertices();
	std::vector<vec3> colors = mesh->readLocalVertexColor();
	uint size = vertices.size();
	std::vector<float> flatVertices, flatColor;
	for (uint i = 0; i < size; i++)
	{
		vec3& vertex = vertices[i];
		vec3& color = colors[i];

		flatVertices.push_back(vertex.x);
		flatColor.push_back(color.x);
		flatVertices.push_back(vertex.y);
		flatColor.push_back(color.y);
		flatVertices.push_back(vertex.z);
		flatColor.push_back(color.z);
	}
	
	glBindVertexArray(VAO);

	// Position attribute
	glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size*3, &flatVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); //TODO: Abstract into shader

	// Color Attribute
	glBindBuffer(GL_ARRAY_BUFFER, colorBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size*3, &flatColor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1); //TODO: abstract into shader

	glBindVertexArray(NULL);

	//Register and Add to object again
	ContextArrays.push_back(VAO);
	mesh->setContextArray(VAO);

	ContextBuffers.push_back(vertexBO);
	ContextBuffers.push_back(colorBO);
	mesh->setContextBuffer(vertexBO, colorBO, size);

	return true;
}

uint Renderer::loadCubeMap(std::vector<const char*> faces)
{
	uint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (uint i = 0; i < faces.size(); ++i)
	{
		//load image from memory
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		
		//send image to cubemap 
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);

		SOIL_free_image_data(image); // remove currently loaded image from memory
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

// References: using the skybox source code from Lab 7
void Renderer::InitSkyBox() 
{
#pragma region loadingSkybox
	//loading skybox from obj
	std::vector<glm::vec3> skybox_vertices;
	std::vector<glm::vec3> skybox_normals; //unused
	std::vector<glm::vec2> skybox_UVs; //unused

	loadOBJ("cube.obj", skybox_vertices, skybox_normals, skybox_UVs);

#pragma endregion from cube.obj

#pragma region generateVAO_VBO_forSkybox
	uint skyboxVAO, skyboxVerticesVBO;

	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);

	glGenBuffers(1, &skyboxVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, skybox_vertices.size() * sizeof(glm::vec3), &skybox_vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

#pragma endregion

#pragma region loadSkyBoxCubeMap
	//prepare skybox cubemap
	std::vector<const GLchar*> faces;
	faces.push_back("right.jpg");
	faces.push_back("left.jpg");
	faces.push_back("top.jpg");
	faces.push_back("bottom.jpg");
	faces.push_back("back.jpg");
	faces.push_back("front.jpg");
	
	glActiveTexture(GL_TEXTURE1);
	GLuint cubemapTexture = loadCubeMap(faces);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
#pragma endregion and send it to GPU

}

Renderer * Renderer::GetInstance()
{
	if (singleton == NULL) {
		singleton = new Renderer();
	}

	return singleton;
}
