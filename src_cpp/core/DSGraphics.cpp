//
// Created by Dario Segura on 2016-07-07.
//

#include "DSGraphics.h"
#include "printToConsole.h"

#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"
#include "ppapi/cpp/module.h"

#include "DSShaderTools.h"
#include "DSVertexShader.h"
#include "DSFragmentShader.h"

typedef struct {
    float positionOne[2];
    float positionTwo[2];
    float colorOne[3];
    float colorTwo[3];
} Vertex;

Vertex vertices[] = {
        {{1, -1}, {1, -1}, {1, 0, 0}, {1, 0, 0}},
        {{1, 1}, {1, 1}, {0, 1, 0}, {0, 1, 0}},
        {{-1, 1}, {-1, 1}, {0, 0, 1}, {0, 0, 1}},
        {{-1, -1}, {-1, -1}, {0, 0, 0}, {0, 0, 0}}
};

const GLubyte indices[] = {
        0, 1, 2,
        2, 3, 0
};

DSGraphics::DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height) {
    m_context = context;
    m_width = width;
    m_height = height;

    m_pixelScaleX = 1.0f / m_width;
    m_pixelScaleY = 1.0f / m_height;

    m_dataPointWidth = m_pixelScaleX * 10.0f;
    m_dataPointHeight = m_pixelScaleY * 10.0f;

    m_vertexShader = compileShader(GL_VERTEX_SHADER, dataSand_vertex_shader_src);
//    printToConsole("m_vertexShader: " + std::to_string(m_vertexShader));

    m_fragmentShader = compileShader(GL_FRAGMENT_SHADER, dataSand_fragment_shader_src);
//    printToConsole("m_fragmentShader: " + std::to_string(m_fragmentShader));

    m_program = linkProgram(m_fragmentShader, m_vertexShader);
//    printToConsole("m_program: " + std::to_string(m_program));

    m_positionSlot01 = glGetAttribLocation(m_program, "positionOne");
    m_colorSlot01 = glGetAttribLocation(m_program, "colorOne");

    m_positionSlot02 = glGetAttribLocation(m_program, "positionTwo");
    m_colorSlot02 = glGetAttribLocation(m_program, "colorTwo");

    for (int i = 0; i < 4; ++i) {
        vertices[i].positionOne[0] *= m_dataPointWidth;
        vertices[i].positionOne[1] *= m_dataPointHeight;

        vertices[i].positionTwo[0] *= m_dataPointWidth * 30.0f;
        vertices[i].positionTwo[1] *= m_dataPointHeight * 30.0f;
    }
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
}

DSGraphics::~DSGraphics() {

}

void DSGraphics::render() {
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    glVertexAttribPointer(m_positionSlot01,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, positionOne)));
    glEnableVertexAttribArray(m_positionSlot01);

    glVertexAttribPointer(m_colorSlot01,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, colorOne)));
    glEnableVertexAttribArray(m_colorSlot01);

    glVertexAttribPointer(m_positionSlot02,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, positionTwo)));
    glEnableVertexAttribArray(m_positionSlot02);

    glVertexAttribPointer(m_colorSlot02,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, colorTwo)));
    glEnableVertexAttribArray(m_colorSlot02);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]),
                   GL_UNSIGNED_BYTE, 0);
}

pp::Graphics3D *DSGraphics::context() {
    return m_context;
}