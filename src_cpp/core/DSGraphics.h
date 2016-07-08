//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSGRAPHICS_H
#define DATASAND_DSGRAPHICS_H

#include <GLES2/gl2.h>
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/utility/completion_callback_factory.h"

typedef struct {
    float positionOne[2];
    float positionTwo[2];
    float colorOne[3];
    float colorTwo[3];
} Vertex;

class DSGraphics {
    int32_t m_width;
    int32_t m_height;

    GLfloat m_pixelScaleX;
    GLfloat m_pixelScaleY;

    GLfloat m_dataPointWidth;
    GLfloat m_dataPointHeight;

    GLfloat m_offsetOriginX;
    GLfloat m_offsetOriginY;

    pp::Graphics3D *m_context;

    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_program;

    GLuint m_positionSlot01;
    GLuint m_positionSlot02;
    GLuint m_colorSlot01;
    GLuint m_colorSlot02;
    GLuint m_interpolationUniform;

    GLfloat m_animationTest;

    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;

    GLuint m_indexBufferCount;

    void _addDataPoint(GLushort *indexBuffer, Vertex *vertexBuffer, int vertexBufferOffset, Vertex &dataPoint);

public:
    DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height);
    ~DSGraphics();

    void render();
    pp::Graphics3D *context();

    void loadData(void *data, int length);
};

#endif //DATASAND_DSGRAPHICS_H
