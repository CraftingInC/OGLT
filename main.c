#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "logging.h"

int main()
{
	glfwInit();
    FILE* lf = fopen("log.txt", "ab");

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL GUI DEMO", NULL, NULL);
	if (!window)
	{
	    log(lf, "ERROR : Failed to create the GLFW window !");
		printf("Failed to create the GLFW window\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    log(lf, "ERROR : Failed to initialize OpenGL context !");
		printf("Failed to initialize OpenGL context\n");
	}

    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
	glViewport(0, 0, 1280, 720);

	log(lf, "INFO : OpenGL Version : %s", glGetString(GL_VERSION));
	printf("OpenGL Version : %s\n", glGetString(GL_VERSION));

	while (!glfwWindowShouldClose(window))
	{
	    glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	log(lf, "INFO : Window Closed");
    fclose(lf);
	glfwDestroyWindow(window);
	glfwTerminate();
}
