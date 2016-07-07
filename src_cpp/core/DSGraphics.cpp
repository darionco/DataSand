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
    float Position[3];
    float Color[4];
} Vertex;

const Vertex Vertices[] = {
        {{1, -1, 0}, {1, 0, 0, 1}},
        {{1, 1, 0}, {0, 1, 0, 1}},
        {{-1, 1, 0}, {0, 0, 1, 1}},
        {{-1, -1, 0}, {0, 0, 0, 1}}
};

const GLubyte Indices[] = {
        0, 1, 2,
        2, 3, 0
};

DSGraphics::DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height) {
    m_context = context;
    m_width = width;
    m_height = height;

    m_vertexShader = compileShader(GL_VERTEX_SHADER, dataSand_vertex_shader_src);
//    printToConsole("m_vertexShader: " + std::to_string(m_vertexShader));

    m_fragmentShader = compileShader(GL_FRAGMENT_SHADER, dataSand_fragment_shader_src);
//    printToConsole("m_fragmentShader: " + std::to_string(m_fragmentShader));

    m_program = linkProgram(m_fragmentShader, m_vertexShader);
//    printToConsole("m_program: " + std::to_string(m_program));

    m_positionSlot = glGetAttribLocation(m_program, "Position");
    m_colorSlot = glGetAttribLocation(m_program, "SourceColor");
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices[0], GL_STATIC_DRAW);
}

DSGraphics::~DSGraphics() {

}

void DSGraphics::render() {
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(m_positionSlot,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(m_positionSlot);

    glVertexAttribPointer(m_colorSlot,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(m_colorSlot);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]),
                   GL_UNSIGNED_BYTE, 0);
}

pp::Graphics3D *DSGraphics::context() {
    return m_context;
}