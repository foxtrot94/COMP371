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
	/*if (shader==NULL || mesh==NULL || !mesh->isInitialized()) {
		//nothing to do here
		return;
	}*/

	// **** REPLACE WHEN SENDING A TEXTURE ****
	if (shader == NULL || mesh == NULL || !mesh->isInitialized() || texture == NULL || !texture->isInitialized()) {
		//nothing to do here
		return;
	}
	

	if (!mesh->isInRenderingContext() && !texture->isInRenderingContext()) {
		//Send it off to the GPU Video Memory
		//FUTURE: Right now all meshes are taken as static, change some day...
		AddToRenderingContext(mesh, texture->isInitialized()? texture:NULL);
	}

	Shader::Uniforms uniform = shader->getUniforms(); //TODO: optimize in the future. Get uniforms outside or something
	glUniformMatrix4fv(uniform.transformMatrixPtr, 1, GL_FALSE, glm::value_ptr(*(Object->getModel())));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->readContextTexture());
	glUniform1i(glGetUniformLocation(shader->getShaderProgram(), "imageTexture"), 0);

	glBindVertexArray(mesh->getContextArray());
	//Basically, draw RenderTarget
	glDrawArrays(GL_TRIANGLES, 0, mesh->getBufferSize());
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

void Renderer::RenderSkyBox(Camera* camera) {
	if (skybox == NULL) 
	{
		InitSkyBox();
	}
	else
	{
		uint skyboxShaderProgram = skyBoxShader->getShaderProgram();
		glUseProgram(skyboxShaderProgram);
		
		glm::mat4 skybox_view = camera->GetView(); // TODO set it to whatever updateCamera has
		glm::mat4 skybox_transform = glm::scale(glm::mat4(1.f),vec3(1000.f));
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

bool Renderer::AddToRenderingContext(GLMesh * mesh, GLTexture* texture)
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

	uint glTexture=0, textureBO=0;
	if (texture != NULL) {
		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		std::vector<unsigned char*> img=texture->readImageData();
		std::vector<float> texels = texture->readLocalTexels();
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, &(img[0]));

		glGenBuffers(1, &textureBO);
		glBindBuffer(GL_ARRAY_BUFFER, textureBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size * 2, &texels[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(2); //TODO: abstract into shader
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	glBindVertexArray(NULL);

	//Register and Add to object again
	ContextArrays.push_back(VAO);
	mesh->setContextArray(VAO);
	
	if (texture) {
		texture->setContextTexture(glTexture);
	}

	ContextBuffers.push_back(vertexBO);
	ContextBuffers.push_back(colorBO);
	mesh->setContextBuffer(vertexBO, colorBO, size);

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
