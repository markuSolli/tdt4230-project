#include <window.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialise window
    GLFWwindow* window = initialiseWindow();

    // Set background color
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render loop
    while(!glfwWindowShouldClose(window)) {
        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll for close event
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // Terminate GLFW
    glfwTerminate();
    
    return EXIT_SUCCESS;
}