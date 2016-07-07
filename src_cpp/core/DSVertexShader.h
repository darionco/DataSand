//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSVERTEXSHADER_H
#define DATASAND_DSVERTEXSHADER_H

const char dataSand_vertex_shader_src[] =
        "attribute vec4 Position;\n"
        "attribute vec4 SourceColor;\n"
        "varying vec4 DestinationColor;\n"
        "void main(void) {\n"
        "    DestinationColor = SourceColor;\n"
        "    gl_Position = Position;\n"
        "}";

#endif //DATASAND_DSVERTEXSHADER_H
