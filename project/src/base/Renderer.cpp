#include "base\Renderer.h"
#include "base\Objects.h"
#include "base\Shader.h"

#include "Camera.h"

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

	for (uchar* img : RawTextureData) {
		GLTexture::cleanImageData(img);
	}
	RawTextureData.clear();

	delete shader;
	delete skyBoxShader;
	delete skybox;
	delete mainWindow;

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
	mainWindow = new Window(outWindow, minWidth, minHeight, windowName);
	return mainWindow;
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
	GLTexture* texture = Object->getTexture();
	if (shader==NULL || mesh==NULL || !mesh->isInitialized()) {
		//nothing to do here
		return;
	}

	if (!mesh->isInRenderingContext()) {
		//Send it off to the GPU Video Memory
		//FUTURE: Right now all meshes are taken as static, change some day...
		AddToRenderingContext(mesh);
	}
	if (!texture->isInRenderingContext()) {
		AddToRenderingContext(texture);
	}

	Shader::Uniforms uniform = shader->getUniforms(); //TODO: optimize in the future. Get uniforms outside or something
	glUniformMatrix4fv(uniform.transformMatrixPtr, 1, GL_FALSE, glm::value_ptr(*(Object->getModel())));

	glBindVertexArray(mesh->getContextArray());

	//Check the texture
	if (texture->isInRenderingContext()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getContext());
		glUniform1i(glGetUniformLocation(shader->getShaderProgram(), "objectTexture"), 0);
	}

	//Basically, draw RenderTarget
	glDrawArrays(GL_TRIANGLES, 0, mesh->getBufferSize());
	
	glBindTexture(GL_TEXTURE_2D,NULL);
	glBindVertexArray(NULL);
}

void Renderer::Render(std::vector<WorldGenericObject*> Objects)
{
	glBindVertexArray(NULL);
	for (WorldGenericObject* object : Objects) {
		Render(object);
	}
	glBindVertexArray(NULL);
}

void Renderer::RenderSkyBox(Camera* camera) {
	if (skybox == NULL) 
	{
		InitSkyBox();
	}
	else
	{
		uint skyboxShaderProgram = skyBoxShader->getShaderProgram();
		glUseProgram(skyboxShaderProgram);
		
		glm::mat4 skybox_view = camera->GetView();
		glm::mat4 skybox_transform = glm::scale(glm::mat4(1.f),vec3(10000.f));
		glm::mat4 projection_matrix = camera->GetProjection(mainWindow);

		Shader::Uniforms uniform = skyBoxShader->getUniforms();

		//might not be necessary, sends to regular shader, view matrix of the skybox
		//glUniformMatrix4fv(shader->getUniforms().viewMatrixPtr, 1, GL_FALSE, glm::value_ptr(skybox_view));

		glUniformMatrix4fv(skyBoxShader->getUniforms().transformMatrixPtr, 1, GL_FALSE, glm::value_ptr(skybox_transform));
		glUniformMatrix4fv(skyBoxShader->getUniforms().viewMatrixPtr, 1, GL_FALSE, glm::value_ptr(skybox_view));
		glUniformMatrix4fv(skyBoxShader->getUniforms().projectMatrixPtr, 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glUniform1i(glGetUniformLocation(skyboxShaderProgram, "skyboxTexture"), 1); //use texture unit 1

		glDepthMask(GL_FALSE);

		glBindVertexArray(skybox->getContextArray());
		glDrawArrays(GL_TRIANGLES, 0, skybox->getVertexBufferSize());
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);
		glUseProgram(shader->getShaderProgram());
	}
	
}

bool Renderer::AddToRenderingContext(GLMesh * mesh)
{
	uint VAO, colorBO, vertexBO, texelBO;
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &vertexBO);
	glGenBuffers(1, &colorBO);
	glGenBuffers(1, &texelBO);

	//synthesize the mesh data since it's been stored as a vec3
	std::vector<vec3> vertices = mesh->readLocalVertices();
	std::vector<vec3> colors = mesh->readLocalVertexColor();
	std::vector<vec2> texels = mesh->readLocalMeshTexels();
	uint size = vertices.size();
	std::vector<float> flatVertices, flatColor, flatTexels;
	for (uint i = 0; i < size; i++)
	{
		vec3& vertex = vertices[i];
		vec3& color = colors[i];
		vec2& texel = texels[i];

		flatVertices.push_back(vertex.x);
		flatColor.push_back(color.x);
		flatVertices.push_back(vertex.y);
		flatColor.push_back(color.y);
		flatVertices.push_back(vertex.z);
		flatColor.push_back(color.z);

		flatTexels.push_back(texel.x);
		flatTexels.push_back(texel.y);
	}

	glBindVertexArray(VAO);

	// Position attribute
	glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size * 3, &flatVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); //TODO: Abstract into shader

	// Color Attribute
	glBindBuffer(GL_ARRAY_BUFFER, colorBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size * 3, &flatColor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1); //TODO: abstract into shader

	// Texel Attribute
	glBindBuffer(GL_ARRAY_BUFFER, texelBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size * 3, &flatTexels[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(2); //TODO: abstract into shader

	glBindVertexArray(NULL);

	//Register and Add to object again
	ContextArrays.push_back(VAO);
	mesh->setContextArray(VAO);

	ContextBuffers.push_back(vertexBO);
	ContextBuffers.push_back(colorBO);
	ContextBuffers.push_back(texelBO);

	mesh->setContextBuffer(vertexBO, colorBO, size);
	mesh->setTexelBuffer(texelBO, size);

	return true;
}

bool Renderer::AddToRenderingContext(GLTexture * texture)
{
	uint textureBuff;
	uchar* img = texture->readImageData();
	if (img == NULL) {
		return false;
	}

	glGenTextures(1, &textureBuff);
	glBindTexture(GL_TEXTURE_2D, textureBuff);

	//TECH DEBT: We're hardcoding this because we're 6 hours away from submission
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Finish and set the texture context
	RawTextureData.insert(img);
	texture->setContextTexture(textureBuff);

	return true;
}


// References: using the skybox source code from Lab 7
void Renderer::InitSkyBox() 
{
	skybox = new SkyBox();
	skybox->loadVertices();

	skybox->genArray();
	skybox->sendVertexBuffer();

	skybox->loadTextures();
}

Renderer * Renderer::GetInstance()
{
	if (singleton == NULL) {
		singleton = new Renderer();
	}

	return singleton;
}
