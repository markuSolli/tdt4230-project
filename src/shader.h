#pragma once
#include <glad/glad.h>
#include <string>

extern const char *vertexShaderSource;
extern const char *fragmentShaderSource;

unsigned int createShader(std::string const &filename, GLenum shaderType);
unsigned int createShaderProgram();