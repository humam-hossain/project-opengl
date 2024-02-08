#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#define WIDTH	800
#define HEIGHT	800

// Vertices coordinates
GLfloat vertices[] =
{
	-0.50f, -0.5f * float(sqrt(3)) / 3,			0.0f, // Lower left corner
	 0.50f, -0.5f * float(sqrt(3)) / 3,			0.0f, // Lower right corner
	 0.00f,  0.5f * float(sqrt(3)) * 2 / 3,		0.0f, // Upper corner
	-0.25f,  0.5f * float(sqrt(3)) / 6,			0.0f, // Inner left
	 0.25f,  0.5f * float(sqrt(3)) / 6,			0.0f, // Inner right
	 0.00f, -0.5f * float(sqrt(3)) / 3,			0.0f, // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1, // Upper triangle
};

int main()
{
	if (!glfwInit()) {
		std::cout << "ERROR: could not initialize GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GL_CONTEXT_PROFILE_MASK, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello world from OpenGL", NULL, NULL);

	if (!window) {
		std::cout << "ERROR: could not create glfw window.\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);
	std::cout << glGetString(GL_VERSION) << "\n";
	
	const char* vertexFile = "res/shaders/default.vert";
	const char* fragmentFile = "res/shaders/default.frag";
	Shader shaderProgram(vertexFile, fragmentFile);

	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkVBO(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();

	glfwTerminate();

	return 0;
}