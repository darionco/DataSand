//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSGRAPHICS_H
#define DATASAND_DSGRAPHICS_H

#include "ppapi/cpp/graphics_3d.h"

class DSGraphics {
    int32_t m_width;
    int32_t m_height;

    pp::Graphics3D *m_context;

public:
    DSGraphics(pp::Graphics3D *context, int32_t width, int32_t height);
    ~DSGraphics();
};

#endif //DATASAND_DSGRAPHICS_H
