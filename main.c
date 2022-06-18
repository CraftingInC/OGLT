#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logging.h"
#include <stdio.h>   // printf()

int main()
{
	glfwInit();
    FILE* lf = fopen("log.txt", "ab");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Template", NULL, NULL);
	if (!window)
	{
	    log(lf, "ERROR : Failed to create the GLFW window !");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    log(lf, "ERROR : Failed to initialize OpenGL context !");
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

