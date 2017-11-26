// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include "ChessBoard.h"
#include "glm/gtc/matrix_transform.hpp"

ChessBoard::ChessBoard(const ShaderProgram & sp): shaderProgram(sp)
{
	Model board("chess_board", shaderProgram, "board.colour.png");
	models.push_back(board);

	squareSize = board.getBoundingBox().x / (float)8;

	Model whitePawn("chess_pawn", shaderProgram, "pawn.colour.white.png");

	for (int i = 1; i <= 8; i++) {
		placePiece(whitePawn, 7, i);
	}

	Model blackPawn("chess_pawn", shaderProgram, "pawn.colour.black.png");

	for (int i = 1; i <= 8; i++) {
		placePiece(blackPawn, 2, i);
	}

	Model whiteRook("chess_rook", shaderProgram, "rook.colour.white.png");
	placePiece(whiteRook, 8, 1);
	placePiece(whiteRook, 8, 8);
	Model whiteKnight("chess_knight", shaderProgram, "knight.colour.white.png");
	placePiece(whiteKnight, 8, 2);
	placePiece(whiteKnight, 8, 7);
	Model whiteBishop("chess_bishop", shaderProgram, "bishop.colour.white.png");
	placePiece(whiteBishop, 8, 3);
	placePiece(whiteBishop, 8, 6);
	Model whiteKing("chess_king", shaderProgram, "king.colour.white.png");
	placePiece(whiteKing, 8, 4);
	Model whiteQueen("chess_queen", shaderProgram, "queen.colour.white.png");
	placePiece(whiteQueen, 8, 5);

	Model blackRook("chess_rook", shaderProgram, "rook.colour.black.png");
	placePiece(blackRook, 1, 1);
	placePiece(blackRook, 1, 8);
	Model blackKnight("chess_knight", shaderProgram, "knight.colour.black.png");
	blackKnight.yaw += 180;
	placePiece(blackKnight, 1, 2);
	placePiece(blackKnight, 1, 7);
	Model blackBishop("chess_bishop", shaderProgram, "bishop.colour.black.png");
	placePiece(blackBishop, 1, 3);
	placePiece(blackBishop, 1, 6);
	Model blackKing("chess_king", shaderProgram, "king.colour.black.png");
	placePiece(blackKing, 1, 4);
	Model blackQueen("chess_queen", shaderProgram, "queen.colour.black.png");
	placePiece(blackQueen, 1, 5);

	pitch += 35;
}

void ChessBoard::draw()
{
	for (Model &m : models) {
		setModelMatrix(m);
		m.draw();
	}
}

void ChessBoard::translate(float x, float y, float z) {
	translation.x += x;
	translation.y += y;
	translation.z += z;
}

void ChessBoard::processKeyboard(int key) {
	switch (key) {
		case GLFW_KEY_EQUAL:
			scaleFactor *= 1.1;
			break;
		case GLFW_KEY_MINUS:
			scaleFactor *= 0.9;
			break;
		case GLFW_KEY_D:
			yaw++;
			break;
		case GLFW_KEY_A:
			yaw--;
			break;
		case GLFW_KEY_W:
			pitch--;
			break;
		case GLFW_KEY_S:
			pitch++;
			break;
		case GLFW_KEY_E:
			roll--;
			break;
		case GLFW_KEY_Q:
			roll++;
			break;
	}
}

BoundingBox ChessBoard::getBoundingBox()
{
	float xMax = models.at(0).getBoundingBox().xMax;
	float xMin = models.at(0).getBoundingBox().xMin;
	float yMax = models.at(0).getBoundingBox().yMax;
	float yMin = models.at(0).getBoundingBox().yMin;
	float zMax = models.at(0).getBoundingBox().zMax;
	float zMin = models.at(0).getBoundingBox().zMin;

	for (Model &m : models) {
		if (m.getBoundingBox().xMax > xMax) {
			xMax = m.getBoundingBox().xMax;
		}
		else if (m.getBoundingBox().xMin < xMin) {
			xMin = m.getBoundingBox().xMin;
		}
		if (m.getBoundingBox().yMax > yMax) {
			yMax = m.getBoundingBox().yMax;
		}
		else if (m.getBoundingBox().yMin < yMin) {
			yMin = m.getBoundingBox().yMin;
		}
		if (m.getBoundingBox().zMax > zMax) {
			zMax = m.getBoundingBox().zMax;
		}
		else if (m.getBoundingBox().zMin < zMin) {
			zMin = m.getBoundingBox().zMin;
		}
	}
	
	boundingBox.x = xMax - xMin;
	boundingBox.y = yMax - yMin;
	boundingBox.z = zMax - zMin;
	boundingBox.xMax = xMax;
	boundingBox.xMin = xMin;
	boundingBox.yMax = yMax;
	boundingBox.yMin = yMin;
	boundingBox.zMax = zMax;
	boundingBox.zMin = zMin;

	return boundingBox;
}

ChessBoard::~ChessBoard()
{
}

void ChessBoard::placePiece(Model piece, int row, int col)
{
	piece.translate((-3.5 * squareSize) + ((col - 1) * squareSize), piece.meshes.at(0).center.y, (3.5 * squareSize) - ((row - 1) * squareSize));
	models.push_back(piece);
}

void ChessBoard::setModelMatrix(Model &piece)
{
	modelMatrix = mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)roll), vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)yaw), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)pitch), vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, vec3(scaleFactor, scaleFactor, scaleFactor));
	modelMatrix = modelMatrix * piece.modelMatrix;
	shaderProgram.bind();
	shaderProgram.setMat4("model", modelMatrix);
}
