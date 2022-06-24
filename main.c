#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logging.h"
#include <stdio.h>   // printf()
#include <stdbool.h> // BOOL

const char *vertexShaderSource = "#version 450 core\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform vec3 positionOffset;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position.xyz + positionOffset.xyz, 1.0);\n"
    "}\n";

const char *fragmentShaderSource = "#version 450 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
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

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                     const GLchar* message, const void* userParam)
{
    (void) source;
    (void) id;
    (void) length;
    (void) userParam;
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

// Few nasty Globals  :P
float greenValue;
float pOffsetY;
GLFWwindow* window;
FILE* lf;

// INPUT
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    if(isMouseMoved() && MSTATS.isLeftMouseDown)
    {
        printf("X: %d / Y: %d\n", MSTATS.xpos, MSTATS.ypos);
    }

    if(MSTATS.isLeftMouseDown)
    {
        greenValue = 0.1f;
    }
    if(MSTATS.isMiddleMouseDown)
    {
        greenValue = 0.5f;
    }
    if(MSTATS.isRightMouseDown)
    {
        greenValue = 0.9f;
    }

    if(MSTATS.wheelState == -1)
    {
        pOffsetY += -0.03f;
        MSTATS.wheelState = 0;
    } else if(MSTATS.wheelState == 1)
    {
        pOffsetY += 0.03f;
        MSTATS.wheelState = 0;
    }
}

void quitProgram()
{
    if(window)
    {
        glfwDestroyWindow(window);
        log(lf, "INFO : Window Closed");
    }
    glfwTerminate();
    fclose(lf);
}

int main()
{
	glfwInit();
    lf = fopen("log.txt", "ab");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "OpenGL Template", NULL, NULL);
	if (!window)
	{
	    log(lf, "ERROR : Failed to create the GLFW window !");
		quitProgram();
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    log(lf, "ERROR : Failed to initialize OpenGL context !");
	    quitProgram();
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glDebugMessageCallback(MessageCallback, 0);

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
        quitProgram();
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
        quitProgram();
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
        quitProgram();
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

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    int positionOffsetLocation = glGetUniformLocation(shaderProgram, "positionOffset");

    greenValue = 1.0f;
    pOffsetY = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
	    processInput(window);
	    glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform3f(positionOffsetLocation, 0.0f, pOffsetY, 0.0f);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
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

	quitProgram();
	return 0;
}

