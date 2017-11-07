// ==========================================================================
// CPSC 453 Assignment #1: Generating and Rendering a Hilbert Curve
// Daniel Dastoor
//  
// Hilbert.h
// Class to create and manipulate Hilbert curves
//
// Author: Daniel Dastoor
// Date:   October 2017
// ==========================================================================

#pragma once
#include <vector>
#include <algorithm>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

class Hilbert {
private:
    int n;
    std::vector<glm::vec4> create(int n);
    static float getScaling(int n);
    int getLevel() {
        return n;
    }
    static std::vector<glm::vec4> transform(std::vector<glm::vec4> vertices, float scale, float angle, float xTranslation, float yTranslation);
public:
    std::vector<float> vertices;
    Hilbert() { }
    enum Mode {
        Lines,
        Rectangles
    };
    void generate(int n, Mode mode);
};