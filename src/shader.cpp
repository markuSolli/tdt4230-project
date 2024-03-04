#include <shader.h>

#include <glad/glad.h> 
#include <fstream>
#include <string>
#include <iostream>

unsigned int createShader(std::string const &filename, GLenum shaderType) {
    // Load GLSL Shader from source
    std::ifstream fd(filename.c_str());
    if (fd.fail()) {
        fprintf(stderr,
            "Something went wrong when attaching the Shader file at \"%s\".\n"
            "The file may not exist or is currently inaccessible.\n",
            filename.c_str());
        return -1;
    }
    
    std::string src = std::string(std::istreambuf_iterator<char>(fd), (std::istreambuf_iterator<char>()));

    // Create shader object
    const char * shaderSource = src.c_str();
    unsigned int shaderId;
    shaderId = glCreateShader(shaderType);

    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);

    int  success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        fprintf(stderr, "Shader compilation failed\n%s\n", infoLog);
    }

    return shaderId;
}

unsigned int createShaderProgram() {
    unsigned int vertexShader = createShader("../res/shaders/shader.vert", GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader("../res/shaders/shader.frag", GL_FRAGMENT_SHADER);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Shader program linking failed\n%s\n", infoLog);
    }

    return shaderProgram;
}