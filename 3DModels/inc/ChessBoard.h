// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#pragma once

#include <vector>

#include "Model.h"
#include "ObjectBase.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class ChessBoard: public ObjectBase
{
public:
	float scaleFactor = 1.0f;
	int pitch = 0;								// rotation about x-axis
	int yaw = 0;								// rotation about y-axis
	int roll = 0;								// rotation about z-axis

	ChessBoard(const ShaderProgram &sp);
	void draw();
	void translate(float x, float y, float z);
	void processKeyboard(int key);
	BoundingBox getBoundingBox();
	~ChessBoard();
private:
	mat4 modelMatrix;
	vec3 translation = vec3(0.0f, 0.0f, 0.0f);
	float squareSize;
	const ShaderProgram &shaderProgram;
	vector<Model> models;
	BoundingBox boundingBox;
	
	void placePiece(Model piece, int row, int col);
	void setModelMatrix(Model &piece);
};

