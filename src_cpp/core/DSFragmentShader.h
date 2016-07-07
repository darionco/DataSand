//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSFRAGMENTSHADER_H
#define DATASAND_DSFRAGMENTSHADER_H

const char dataSand_fragment_shader_src[] =
        "varying lowp vec4 DestinationColor;\n"
        "void main(void) {\n"
        "    gl_FragColor = DestinationColor;\n"
        "}";

#endif //DATASAND_DSFRAGMENTSHADER_H
