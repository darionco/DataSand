//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSVERTEXSHADER_H
#define DATASAND_DSVERTEXSHADER_H

const char dataSand_vertex_shader_src[] =
        "attribute vec2 positionOne;\n"
        "attribute vec3 colorOne;\n"
        "attribute vec2 positionTwo;\n"
        "attribute vec3 colorTwo;\n"
		"attribute float timeMultiplier;\n"
        "uniform float interpolation;\n"
		"uniform float change;\n"
        "varying vec4 DestinationColor;\n"
		"float backEaseOut(float delta, float start, float change, float overshot) {\n"
		"    float time = delta - 1.0;\n"
		"    return change * (time * time * ((overshot + 1.0) * time + overshot) + 1.0) + start;\n"
		"}\n"
        "void main(void) {\n"
		"    float i = clamp((interpolation * 2.0) - (timeMultiplier / 65535.0), 0.0, 1.0);\n"
		"    float start = clamp((change * -1.0), 0.0, 1.0);\n"
		"    float delta = abs(start - i);\n"
		"    float ease = backEaseOut(delta, start, change, 0.5);\n"
        "    DestinationColor = vec4(mix(colorOne, colorTwo, ease) / 255.0, 1.);\n"
		"    vec2 position = ((mix(positionOne, positionTwo, ease) / 65535.0) * 2.0) - 1.0;\n"
        "    gl_Position = vec4(position, 0., 1.);\n"
        "}";

#endif //DATASAND_DSVERTEXSHADER_H
