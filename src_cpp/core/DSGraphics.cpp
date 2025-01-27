//
// Created by Dario Segura on 2016-07-07.
//

#include "DSGraphics.h"
#include "printToConsole.h"

#include <math.h>
#include <sys/time.h>

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

const GLuint g_indices[] = {
        0, 1, 2,
        2, 3, 0
};

DSGraphics::DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height) {
    m_context = context;
    m_width = width;
    m_height = height;

    m_pixelScaleX = floor(65535.0f / m_width);
    m_pixelScaleY = floor(65535.0f / m_height);
	
	printToConsole("width:" + std::to_string(m_width) + " height:" + std::to_string(m_height) + " px:" + std::to_string(m_pixelScaleX) + " py:" + std::to_string(m_pixelScaleY));

    m_dataPointWidth = m_pixelScaleX * 2.0f;
    m_dataPointHeight = m_pixelScaleY * 2.0f;

    m_offsetOriginX = -0.9f;
    m_offsetOriginY = -0.9f;

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
	
	m_timeMultiplierSlot = glGetAttribLocation(m_program, "timeMultiplier");

    m_interpolationUniform = glGetUniformLocation(m_program, "interpolation");
	m_changeUniform = glGetUniformLocation(m_program, "change");

    m_indexBufferCount = 0;

    m_animationTest = 0.0f;
	m_animationChange = 1.0f;

    m_animating = false;
    m_waitTime = 3.0;
    m_transitionTime = 1.5;
    m_elapsedTime = 0;
    m_animationTarget = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    m_newTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    m_oldTime = m_newTime;
}

DSGraphics::~DSGraphics() {

}

void DSGraphics::render() {

    struct timeval tp;
    gettimeofday(&tp, NULL);
    m_newTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    double delta = fmin(0.3, ((double)(m_newTime - m_oldTime)) / 1000.0);
    m_oldTime = m_newTime;

    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_indexBufferCount) {
        return;
    }

    glUseProgram(m_program);


    m_elapsedTime += delta;
    if (m_elapsedTime < 0) m_elapsedTime = 0;

    if (m_animating && m_elapsedTime >= m_transitionTime) {
        m_elapsedTime = 0;
        m_animating = false;
    } else if (!m_animating && m_elapsedTime >= m_waitTime) {
        m_animating = true;
        m_elapsedTime = 0;
        m_animationTest = m_animationTarget;
        m_animationTarget = (m_animationTarget == 0) ? 1.0 : 0;
		m_animationChange = (m_animationTarget == 0) ? -1.0 : 1.0;
    }

    if (m_animating) {
        m_animationTest += (delta / m_transitionTime) * m_animationChange;
        glUniform1f(m_interpolationUniform, m_animationTest);
    } else {
        glUniform1f(m_interpolationUniform, m_animationTarget);
    }
	
	glUniform1f(m_changeUniform, m_animationChange);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    glVertexAttribPointer(m_positionSlot01,
                          2,
                          GL_UNSIGNED_SHORT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, positionOne)));
    glEnableVertexAttribArray(m_positionSlot01);

    glVertexAttribPointer(m_colorSlot01,
                          3,
                          GL_UNSIGNED_BYTE,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, colorOne)));
    glEnableVertexAttribArray(m_colorSlot01);

    glVertexAttribPointer(m_positionSlot02,
                          2,
                          GL_UNSIGNED_SHORT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, positionTwo)));
    glEnableVertexAttribArray(m_positionSlot02);

    glVertexAttribPointer(m_colorSlot02,
                          3,
                          GL_UNSIGNED_BYTE,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, colorTwo)));
    glEnableVertexAttribArray(m_colorSlot02);
	
	glVertexAttribPointer(m_timeMultiplierSlot,
                          1,
                          GL_UNSIGNED_SHORT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, timeMultiplier)));
    glEnableVertexAttribArray(m_timeMultiplierSlot);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glDrawElements(GL_TRIANGLES, m_indexBufferCount, GL_UNSIGNED_INT, 0);
}

pp::Graphics3D *DSGraphics::context() {
    return m_context;
}

void DSGraphics::loadData(void *data, int length) {
    printToConsole("DSGraphics::loadData: " + std::to_string(length));
    Vertex_large *rawData = static_cast<Vertex_large*>(data);

    size_t indexBufferCount = length * 6;
    size_t vertexBufferCount = length * 4;

    size_t indexBufferLength = indexBufferCount * sizeof(GLuint);
    size_t vertexBufferLength = vertexBufferCount * sizeof(Vertex);

    GLuint *indices = (GLuint*)malloc(indexBufferLength);
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

void DSGraphics::_addDataPoint(GLuint *indexBuffer, Vertex *vertexBuffer, int vertexBufferOffset, Vertex_large &dataPoint) {

    float colors[5][3] = {
            { 105.0f,210.0f,231.0f },
            { 167.0f,219.0f,216.0f },
            { 224.0f,228.0f,204.0f },
            { 243.0f,134.0f,48.0f },
            { 250.0f,105.0f,0.0f }
    };

    const float sizeFactor = 500.0f;

    for (int i = 0; i < 6; ++i) {
        indexBuffer[i] = g_indices[i] + vertexBufferOffset;
    }

    int c = ((int)(dataPoint.positionTwo[0]/100));

    for (int i = 0; i < 4; ++i) {

        for (int j = 0; j < 3; ++j) {
            vertexBuffer[i].colorOne[j] = dataPoint.colorOne[j];// colors[c%5][j];
            vertexBuffer[i].colorTwo[j] = dataPoint.colorTwo[j];// colors[c%5][j];
        }

        vertexBuffer[i].positionOne[0] = 	(g_vertices[i].positionOne[0] * m_dataPointWidth) + 
											m_dataPointWidth +
											((fmod(dataPoint.positionOne[0], sizeFactor) / sizeFactor) * (65535.0f - (m_dataPointWidth * 2.0f)));
        vertexBuffer[i].positionOne[1] = 	(g_vertices[i].positionOne[1] * m_dataPointHeight) +
											m_dataPointHeight +
											((fmod(dataPoint.positionOne[1], sizeFactor) / sizeFactor) * (65535.0f - (m_dataPointHeight * 2.0f)));

        vertexBuffer[i].positionTwo[0] = 	(g_vertices[i].positionTwo[0] * m_dataPointWidth) + 
											m_dataPointWidth +
											((fmod(dataPoint.positionTwo[0], sizeFactor) / sizeFactor) * (65535.0f - (m_dataPointWidth * 2.0f)));
        vertexBuffer[i].positionTwo[1] = 	(g_vertices[i].positionTwo[1] * m_dataPointHeight) +
											m_dataPointHeight +
											((fmod(dataPoint.positionTwo[1], sizeFactor) / sizeFactor) * (65535.0f - (m_dataPointHeight * 2.0f)));
		
		vertexBuffer[i].timeMultiplier = floor((((float)vertexBuffer[i].positionTwo[0]) * 0.8) + floor(((float)vertexBuffer[i].positionTwo[1]) * 0.2));
		
		// printToConsole("positionOne x:" + std::to_string(vertexBuffer[i].positionOne[0]) + " y:" + std::to_string(vertexBuffer[i].positionOne[1]));
    }
}