// ==========================================================================
// CPSC 453 Assignment #1: Generating and Rendering a Hilbert Curve
// Daniel Dastoor
//  
// Hilbert.cpp
// Class to create and manipulate Hilbert curves
//
// Author: Daniel Dastoor
// Date:   October 2017
// ==========================================================================

#include "Hilbert.h"
#include <cmath>

using std::vector;
using std::pow;
using std::reverse;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::scale;
using glm::radians;

// Generates a Hilbert curve as a set of vertices for either a line or rectangle rendering representation
void Hilbert::generate(int n, Mode mode) {
    this->n = n;
    vector<vec4> vertices = Hilbert::create(n);
    mat4 scaling = glm::scale(mat4(), vec3(0.95f, 0.95f, 0.0f)); // Scale the entire curve by 0.95 to avoid the edges of the window
    this->vertices.clear();
    if (mode == Mode::Lines) {
        for (vec4& v : vertices) {
            v = scaling * v; 
            // Insert x and y coordinates of each vec4 into vertex array
            this->vertices.push_back(v.x);
            this->vertices.push_back(v.y);
        }
    } else if (mode == Mode::Rectangles) {
        for (vec4& v : vertices) {
            v = scaling * v;
        }
        float width = 0.005f; // Half of rectangle width
        for (int i = 0; i < vertices.size() - 1; i++) {
            // Load two vertices, and compute a rectangle of width 0.01 between them
            vec4 v1 = vertices[i];
            vec4 v2 = vertices[i + 1];
            //
            if (std::fabs(v1.y - v2.y) > 0.000001) { // Check if the two floating point numbers are significantly different
                // Insert two triangles into vertex array to define rectangle
                this->vertices.push_back(v1.x + width);
                this->vertices.push_back(v1.y);
                this->vertices.push_back(v2.x + width);
                this->vertices.push_back(v2.y);
                this->vertices.push_back(v1.x - width);
                this->vertices.push_back(v1.y);

                this->vertices.push_back(v2.x + width);
                this->vertices.push_back(v2.y);
                this->vertices.push_back(v2.x - width);
                this->vertices.push_back(v2.y);
                this->vertices.push_back(v1.x - width);
                this->vertices.push_back(v1.y);
            } else {
                // Insert two triangles into vertex array to define rectangle
                this->vertices.push_back(v1.x);
                this->vertices.push_back(v1.y - width);
                this->vertices.push_back(v2.x);
                this->vertices.push_back(v2.y - width);
                this->vertices.push_back(v1.x);
                this->vertices.push_back(v1.y + width);

                this->vertices.push_back(v2.x);
                this->vertices.push_back(v2.y + width);
                this->vertices.push_back(v1.x);
                this->vertices.push_back(v1.y + width);
                this->vertices.push_back(v2.x);
                this->vertices.push_back(v2.y - width);
            }
        }
    }
}

// Creates a vec4 vector that defines a Hilbert curve of recursive level n
vector<vec4> Hilbert::create(int n) {
    if (n == 1) {
        // Base case
        vector<vec4> vertices;
        vertices.push_back(vec4(-1.0, -1.0, 0.0f, 1.0f));
        vertices.push_back(vec4(-1.0, 1.0, 0.0f, 1.0f));
        vertices.push_back(vec4(1.0, 1.0, 0.0f, 1.0f));
        vertices.push_back(vec4(1.0, -1.0, 0.0f, 1.0f));
        return vertices;
    } else if (n > 1) {
        // Recursive case
        // Get previous scale factor and undo it before applying the current scale factor
        // to ensure correct scaling
        float previousScaleFactor = Hilbert::getScaling(n - 1);
        float removeScalingFactor = 1.0f / previousScaleFactor;
        float scaleFactor = (1.0f / (pow(2, n) - 1.0f)) * removeScalingFactor;
        float translationFactor = 2.0f / (pow(2, n) - 1.0f);
        // Enlarge curve to ensure curve fills the entire window
        if (n > 2) {
            translationFactor *= pow(2, (n - 2));
        }
        vector<vector<vec4>> subHilberts;
        // Recursive call to get a n-1 Hilbert curve
        vector<vec4> subHilbert = Hilbert::create(n - 1);
        // Copy the curve 4 times
        subHilberts.push_back(subHilbert);
        subHilberts.push_back(subHilbert);
        subHilberts.push_back(subHilbert);
        subHilberts.push_back(subHilbert);

        // Apply transformations to curve to build up Hilbert curve using the n-1 curve
        subHilberts[0] = Hilbert::transform(subHilberts[0], scaleFactor, -90.0f, -translationFactor, -translationFactor);
        reverse(subHilberts[0].begin(), subHilberts[0].end());
        subHilberts[1] = Hilbert::transform(subHilberts[1], scaleFactor, 0, -translationFactor, translationFactor);
        subHilberts[2] = Hilbert::transform(subHilberts[2], scaleFactor, 0, translationFactor, translationFactor);
        subHilberts[3] = Hilbert::transform(subHilberts[3], scaleFactor, 90.0f, translationFactor, -translationFactor);
        reverse(subHilberts[3].begin(), subHilberts[3].end());

        subHilberts[0].insert(subHilberts[0].end(), subHilberts[1].begin(), subHilberts[1].end());
        subHilberts[0].insert(subHilberts[0].end(), subHilberts[2].begin(), subHilberts[2].end());
        subHilberts[0].insert(subHilberts[0].end(), subHilberts[3].begin(), subHilberts[3].end());

        return subHilberts[0];
    } else {
        return vector<vec4>();
    }
}

// Transforms a series of vec4 vertices by first scaling the vertices by the scale amount,
// then rotating the vertices by the angle in degrees, and finally by translating the vertices
// by xTranslation and yTranslation
vector<vec4> Hilbert::transform(vector<vec4> vertices, float scale, float angle, float xTranslation, float yTranslation) {
    mat4 translation = glm::translate(mat4(), vec3(xTranslation, yTranslation, 0.0f));
    mat4 rotation = glm::rotate(translation, radians(angle), vec3(0.0f, 0.0f, 1.0f));
    mat4 transformation = glm::scale(rotation, vec3(scale, scale, 0.0f));
    for (vec4& v : vertices) {
        v = transformation * v;
    }
    return vertices;
}

// Gets the scaling factor for a given recursive level n
float Hilbert::getScaling(int n) {
    return 1.0f / (pow(2, n) - 1.0f);
}