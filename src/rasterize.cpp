#include <rasterize.h>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

#include <window.h>
#include <scene.h>

void rasterize() {
    // Initialise window
    GLFWwindow* window = initialiseWindow();

    // SETUP OPENGL
    // ==============

    // Set background color
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Initialise scene
    initialiseScene(window);

    // Render loop
    while(!glfwWindowShouldClose(window)) {
        // Clear color
        glClear(GL_COLOR_BUFFER_BIT);

        // Update and render scene
        updateScene(window);

        renderScene(window);

        // Swap buffers and poll for close event
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // Terminate GLFW
    glfwTerminate();
}