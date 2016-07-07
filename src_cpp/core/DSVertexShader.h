//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSVERTEXSHADER_H
#define DATASAND_DSVERTEXSHADER_H

const char dataSand_vertex_shader_src[] =
        "attribute vec2 positionOne;\n"
        "attribute vec3 colorOne;\n"
        "attribute vec2 positionTwo;\n"
        "attribute vec3 colorTwo;\n"
        "varying vec4 DestinationColor;\n"
        "void main(void) {\n"
        "    DestinationColor = vec4(mix(colorOne, colorTwo, 0.5), 1.);\n"
        "    gl_Position = vec4(mix(positionOne, positionTwo, 0.5), 0., 1.);\n"
        "}";

#endif //DATASAND_DSVERTEXSHADER_H
