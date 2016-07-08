//
// Created by Dario Segura on 2016-07-07.
//

#include "DSGraphics.h"
#include "printToConsole.h"

#include <math.h>

#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"
#include "ppapi/cpp/module.h"

#include "DSShaderTools.h"
#include "DSVertexShader.h"
#include "DSFragmentShader.h"

Vertex g_vertices[] = {
        {{1, -1}, {1, -1}, {1, 0, 0}, {1, 1, 0}},
        {{1, 1}, {1, 1}, {0, 1, 0}, {0, 1, 1}},
        {{-1, 1}, {-1, 1}, {0, 0, 1}, {1, 0, 1}},
        {{-1, -1}, {-1, -1}, {0, 0, 0}, {1, 1, 1}}
};

const GLubyte g_indices[] = {
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

    m_offsetOriginX = -0.5f;
    m_offsetOriginY = -0.5f;

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

    m_interpolationUniform = glGetUniformLocation(m_program, "interpolation");

    m_indexBufferCount = 0;

    m_animationTest = 0.0f;
}

DSGraphics::~DSGraphics() {

}

void DSGraphics::render() {
    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_indexBufferCount) {
        return;
    }

    glUseProgram(m_program);

    m_animationTest += 0.05;
    glUniform1f(m_interpolationUniform, (sin(m_animationTest) + 1.0) / 2.0);

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
    glDrawElements(GL_TRIANGLES, m_indexBufferCount, GL_UNSIGNED_SHORT, 0);
}

pp::Graphics3D *DSGraphics::context() {
    return m_context;
}

void DSGraphics::loadData(void *data, int length) {
    printToConsole("DSGraphics::loadData: " + std::to_string(length));
    Vertex *rawData = static_cast<Vertex*>(data);

    size_t indexBufferCount = length * 6;
    size_t vertexBufferCount = length * 4;

    size_t indexBufferLength = indexBufferCount * sizeof(GLushort);
    size_t vertexBufferLength = vertexBufferCount * sizeof(Vertex);

    GLushort *indices = (GLushort*)malloc(indexBufferLength);
    Vertex *vertices = (Vertex*)malloc(vertexBufferLength);

    for (int i = 0; i < length; ++i) {
        int vertexBuferOffset = i * 4;
        _addDataPoint(&indices[i * 6], &vertices[vertexBuferOffset], vertexBuferOffset, rawData[i]);
    }

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferLength, &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferLength, &indices[0], GL_STATIC_DRAW);

    free(vertices);
    free(indices);

    m_indexBufferCount = indexBufferCount;

    printToConsole("DSGraphics::loadData: END");
}

void DSGraphics::_addDataPoint(GLushort *indexBuffer, Vertex *vertexBuffer, int vertexBufferOffset, Vertex &dataPoint) {
    for (int i = 0; i < 6; ++i) {
        indexBuffer[i] = g_indices[i] + vertexBufferOffset;
    }

    for (int i = 0; i < 4; ++i) {
        std::copy(std::begin(dataPoint.colorOne), std::end(dataPoint.colorOne), std::begin(vertexBuffer[i].colorOne));
        std::copy(std::begin(dataPoint.colorTwo), std::end(dataPoint.colorTwo), std::begin(vertexBuffer[i].colorTwo));

        vertexBuffer[i].positionOne[0] = m_offsetOriginX + (g_vertices[i].positionOne[0] * m_dataPointWidth) + (dataPoint.positionOne[0] / 1000);
        vertexBuffer[i].positionOne[1] = m_offsetOriginY + (g_vertices[i].positionOne[1] * m_dataPointHeight) + (dataPoint.positionOne[1] / 1000);

        vertexBuffer[i].positionTwo[0] = m_offsetOriginX + (g_vertices[i].positionTwo[0] * m_dataPointWidth) + (dataPoint.positionTwo[0] / 1000);
        vertexBuffer[i].positionTwo[1] = m_offsetOriginY + (g_vertices[i].positionTwo[1] * m_dataPointHeight) + (dataPoint.positionTwo[1] / 1000);
    }
}