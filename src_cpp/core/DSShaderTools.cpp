//
// Created by Dario Segura on 2016-07-07.
//

#include "DSShaderTools.h"
#include "printToConsole.h"

GLuint compileShader(GLenum type, const char* data) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, NULL);
    glCompileShader(shader);

    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        // Shader failed to compile, let's see what the error is.
        char buffer[1024];
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(buffer), &length, &buffer[0]);
        printToConsole(std::string("Shader failed to compile: ") + buffer);
        return 0;
    }

    return shader;
}

GLuint linkProgram(GLuint frag_shader, GLuint vert_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, frag_shader);
    glAttachShader(program, vert_shader);
    glLinkProgram(program);

    GLint link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        // Program failed to link, let's see what the error is.
        char buffer[1024];
        GLsizei length;
        glGetProgramInfoLog(program, sizeof(buffer), &length, &buffer[0]);
        printToConsole(std::string("Program failed to link: ") + buffer);
        return 0;
    }

    return program;
}