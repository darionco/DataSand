//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSSHADERTOOLS_H
#define DATASAND_DSSHADERTOOLS_H

#include <GLES2/gl2.h>

GLuint compileShader(GLenum type, const char* data);
GLuint linkProgram(GLuint frag_shader, GLuint vert_shader);

#endif //DATASAND_DSSHADERTOOLS_H
