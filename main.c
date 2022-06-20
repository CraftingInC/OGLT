#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logging.h"
#include <stdio.h>   // printf()
#include <stdbool.h> // BOOL

struct mouseStats {
    int xpos;
    int ypos;
    bool mouseMoved;
    bool isLeftMouseDown;
    bool isMiddleMouseDown;
    bool isRightMouseDown;
    int wheelState;
} MSTATS;

bool isMouseMoved()
{
    return MSTATS.mouseMoved;
}

void setMouseMovedFalse()
{
    MSTATS.mouseMoved = false;
}

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    MSTATS.xpos = (int)(xposIn);
    MSTATS.ypos = (int)(yposIn);

    MSTATS.mouseMoved = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        MSTATS.isLeftMouseDown = true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        MSTATS.isLeftMouseDown = false;
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        MSTATS.isMiddleMouseDown = true;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        MSTATS.isMiddleMouseDown = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        MSTATS.isRightMouseDown = true;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        MSTATS.isRightMouseDown = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset < 0)
    {
        MSTATS.wheelState = -1;
    } else if(yoffset > 0)
    {
        MSTATS.wheelState = 1;
    }
}

// INPUT
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    if(isMouseMoved())
    {
        printf("X: %d / Y: %d\n", MSTATS.xpos, MSTATS.ypos);
    }

    if(MSTATS.isLeftMouseDown)
    {
        printf("Left Mouse Button Pressed\n");
    }
    if(MSTATS.isMiddleMouseDown)
    {
        printf("Middle Mouse Button Pressed\n");
    }
    if(MSTATS.isRightMouseDown)
    {
        printf("Right Mouse Button Pressed\n");
    }

    if(MSTATS.wheelState == -1)
    {
        printf("Scrolling DOWN\n");
        MSTATS.wheelState = 0;
    } else if(MSTATS.wheelState == 1)
    {
        printf("Scrolling UP\n");
        MSTATS.wheelState = 0;
    }
}

const char *vertexShaderSource = "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *fragmentShaderSource = "#version 450 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
	glViewport(0, 0, 1280, 720);

	log(lf, "INFO : OpenGL Version : %s", glGetString(GL_VERSION));
	printf("OpenGL Version : %s\n", glGetString(GL_VERSION));

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        log(lf, "ERROR : SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        log(lf, "ERROR : SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        log(lf, "ERROR : SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
	    processInput(window);
	    glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		setMouseMovedFalse();
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	log(lf, "INFO : Window Closed");
    fclose(lf);
}

