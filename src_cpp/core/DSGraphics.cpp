//
// Created by Dario Segura on 2016-07-07.
//

#include "DSGraphics.h"
#include "printToConsole.h"

#include <GLES2/gl2.h>
#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"
#include "ppapi/cpp/module.h"

DSGraphics::DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height) {
    m_context = context;
    m_width = width;
    m_height = height;
}

DSGraphics::~DSGraphics() {

}
