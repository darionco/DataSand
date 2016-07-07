//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSGRAPHICS_H
#define DATASAND_DSGRAPHICS_H

#include <GLES2/gl2.h>
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/utility/completion_callback_factory.h"

class DSGraphics {
    int32_t m_width;
    int32_t m_height;

    pp::Graphics3D *m_context;

    GLuint m_vertexShader;
    GLuint m_fragmentShader;

    GLuint m_positionSlot;
    GLuint m_colorSlot;
    GLuint m_program;

    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;

public:
    DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height);
    ~DSGraphics();

    void render();
    pp::Graphics3D *context();
};

#endif //DATASAND_DSGRAPHICS_H
