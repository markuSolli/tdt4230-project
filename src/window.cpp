#include <window.h>
#include <glad/glad.h> 
#include <iostream>

const int windowWidth = 640;
const int windowHeight = 480;
const char* windowTitle = "Window";

// Callback for GLFW errors
void glfwErrorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW returned an error:\n\t%s (%i)\n", description, error);
}

// Callback for resize events
void framebufferSizeCallback(__attribute__((unused)) GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initialiseWindow() {
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Could not start GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Set core window options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable GLFW error callback
    glfwSetErrorCallback(glfwErrorCallback);

    // Create window using GLFW
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Could not open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Enable resize event callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); 

    // Let the window be the current OpenGL context
    glfwMakeContextCurrent(window);

    // Initialise glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, windowWidth, windowHeight);

    return window;
}