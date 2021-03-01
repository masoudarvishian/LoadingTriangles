#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Vertices.h"
#include "Shader.h"

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void prepareData(unsigned int VAO, unsigned int VBO, GLsizeiptr size, const float vertices[]);
void bindAndDraw(unsigned int VAO);
void prepareUseShader(const Shader &shader, float &colorTimer);

const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 900;

const char *vertexPath = "vertexShader.glsl";
const char *fragmentPath = "fragmentShader.glsl";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Loading...", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create the window!\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load opengl function pointers!\n";
		glfwTerminate();
		return -1;
	}

	Shader firstShader(vertexPath, fragmentPath);
	Shader secondShader(vertexPath, fragmentPath);
	Shader thirdShader(vertexPath, fragmentPath);
	Shader forthShader(vertexPath, fragmentPath);
	Shader fifthShader(vertexPath, fragmentPath);
	Shader sixthShader(vertexPath, fragmentPath);

	unsigned int VAOs[6], VBOs[6];
	glGenVertexArrays(6, VAOs);
	glGenBuffers(6, VBOs);

	prepareData(VAOs[0], VBOs[0], sizeof(firstTriangle), firstTriangle);
	prepareData(VAOs[1], VBOs[1], sizeof(secondTriangle), secondTriangle);
	prepareData(VAOs[2], VBOs[2], sizeof(thirdTriangle), thirdTriangle);
	prepareData(VAOs[3], VBOs[3], sizeof(forthTriangle), forthTriangle);
	prepareData(VAOs[4], VBOs[4], sizeof(fifthTriangle), fifthTriangle);
	prepareData(VAOs[5], VBOs[5], sizeof(sixthTriangle), sixthTriangle);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float colorTimer = glfwGetTime()*5.0f;

		prepareUseShader(firstShader, colorTimer);
		bindAndDraw(VAOs[0]);

		prepareUseShader(secondShader, colorTimer);
		bindAndDraw(VAOs[1]);

		prepareUseShader(thirdShader, colorTimer);
		bindAndDraw(VAOs[2]);

		prepareUseShader(forthShader, colorTimer);
		bindAndDraw(VAOs[3]);

		prepareUseShader(fifthShader, colorTimer);
		bindAndDraw(VAOs[4]);

		prepareUseShader(sixthShader, colorTimer);
		bindAndDraw(VAOs[5]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(firstShader.ID);

	glfwTerminate();

	return 0;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void prepareData(unsigned int VAO, unsigned int VBO, GLsizeiptr size, const float vertices[])
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void bindAndDraw(unsigned int VAO)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void prepareUseShader(const Shader &shader, float &colorTimer)
{
	shader.use();
	colorTimer = colorTimer+0.5f;
	float color = (sin(colorTimer)/2.0f)+0.5f;
	shader.set4Float("uniColor", color, color, color, 1.0f);
}