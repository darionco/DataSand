//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSGRAPHICS_H
#define DATASAND_DSGRAPHICS_H

#include <GLES2/gl2.h>
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/utility/completion_callback_factory.h"

typedef struct {
    float positionOne[2]; // 8 = 64
    float positionTwo[2]; // 8 = 64
    float colorOne[3]; // 12 = 96
    float colorTwo[3]; // 12 = 96
} Vertex_large; // 64 + 64 + 96 + 96 = 320

typedef struct {
	GLushort positionOne[2]; // 4 = 32
	GLushort positionTwo[2]; // 4 = 32
	GLubyte colorOne[3]; // 3 = 24
	GLubyte colorTwo[3]; // 3 = 24
	GLushort timeMultiplier; // 2 = 16
} Vertex; // 32 + 32 + 24 + + 24 + 16 = 128

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
	GLuint m_timeMultiplierSlot;
    GLuint m_interpolationUniform;
	GLuint m_changeUniform;

    GLfloat m_animationTest;
	GLfloat m_animationChange;

    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;

    GLuint m_indexBufferCount;

    double m_newTime;
    double m_oldTime;

    bool m_animating;
    double m_elapsedTime;
    double m_waitTime;
    double m_transitionTime;
    double m_animationTarget;

    void _addDataPoint(GLuint *indexBuffer, Vertex *vertexBuffer, int vertexBufferOffset, Vertex_large &dataPoint);

public:
    DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height);
    ~DSGraphics();

    void render();
    pp::Graphics3D *context();

    void loadData(void *data, int length);
};

#endif //DATASAND_DSGRAPHICS_H
