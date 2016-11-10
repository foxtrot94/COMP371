#include "main.h"
#include "input.h"
#include "utils.h"
#include "Renderer.h"
#include "BaseObjects.h"
#include "Shader.h"

using namespace std;

//TODO: Remove globals, upgrade to C++ (check main.h)
glm::vec3 cameraTranslation = glm::vec3(0.0f,0.f,260.f);
glm::vec3 cameraDirectionPoint = glm::vec3(0.f, 0.f, -1.f);

glm::vec3 objectRotation = glm::vec3(0.f);

float framerate = 0.f;
float deltaTime = 99.f;

//Entry point
int main()
{
	//Initialize
	GLFWwindow* window;
	glm::mat4 model, view, projection; //matrix projections
	int width, height; //viewport 

	std::cout << "Starting OpenGL 3.3 using GLFW" << std::endl;
	//AppInit("Shin Sekai - COMP371 OpenGL Project", HEIGHT, WIDTH, &window);
	//SetInputCallbacks(window);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	//glfwGetFramebufferSize(window, &width, &height);

	Shader shaderBuilder("vertex.shader", "fragment.shader");
	GLuint shaderObject = shaderBuilder.getShaderProgram();

	//Set up the VAO, the VBOs and the EBO
	GLuint VBO, VAO, colorVBO;
	GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &colorVBO);

	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray(VAO);

	glBindVertexArray(0); // Unbind VAO

	GLuint transformLoc = glGetUniformLocation(shaderObject, "model");
	GLuint viewMatrixLoc = glGetUniformLocation(shaderObject, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderObject, "projection");

	//Game loop
	std::cout << "Initialization complete, starting game" << std::endl;
	float lastFrame = 0.f, thisFrame=0.f;
	//TODO: Abstract most of this into a RenderTarget model.
	while (false){
		thisFrame = (float)glfwGetTime();
		deltaTime = thisFrame - lastFrame;
		framerate = 1.f / deltaTime;
		lastFrame = thisFrame;

		glfwPollEvents();
		//glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black Background
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		model = glm::scale(model, glm::vec3(1.0f));
		//If we've received a rotation, rotate it
		//TODO: Change this! this is horrible.
		if (objectRotation.x != 0.f || objectRotation.y != 0.f || objectRotation.z != 0.f) {
			model = glm::rotate(model, 1.f/60.f, objectRotation);
			objectRotation = glm::vec3(0.0f);
		}

		view = glm::lookAt(
			cameraTranslation,							//Position
			cameraTranslation + cameraDirectionPoint,	//looks at Point
			glm::vec3(0.0f, 1.0f, 0.0f)
			);

		projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f); //BUG WAS HERE!!!!

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		//Basically, draw RenderTarget
		//glDrawElements(GL_TRIANGLES, triangleIndicesSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//Cleanup now
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}