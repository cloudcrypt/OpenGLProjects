#include "ChessBoard.h"


ChessBoard::ChessBoard(const ShaderProgram & sp): shaderProgram(sp)
{
	Model board("chess_board", shaderProgram, "board.colour.png");
	board.pitch += 45;
	models.push_back(board);

	float squareSize = board.getBoundingBox().x / (float)64;

	for (int i = -3; i < 5; i++) {
		Model pawn("chess_pawn", shaderProgram, "pawn.colour.white.png");
		pawn.pitch += 45;
		pawn.scaleFactor = 0.17;
		pawn.translate((i - 0.5) * squareSize, 0.5 * squareSize, -3.5 * squareSize);
		models.push_back(pawn);
	}

	for (int i = -3; i < 5; i++) {
		Model pawn("chess_pawn", shaderProgram, "pawn.colour.black.png");
		pawn.pitch += 45;
		pawn.scaleFactor = 0.17;
		pawn.translate((i - 0.5) * squareSize, 0.5 * squareSize, 3.5 * squareSize);
		models.push_back(pawn);
	}
	/*Model pawn1("chess_pawn", shaderProgram, "pawn.colour.white.png");
	pawn1.scaleFactor = 0.17;
	pawn1.translate(-2 * squareSize, 0, 0);
	models.push_back(pawn1);
	Model pawn2("chess_pawn", shaderProgram, "pawn.colour.white.png");
	pawn2.scaleFactor = 0.17;
	pawn2.translate(-3 * squareSize, 0, 0);
	models.push_back(pawn2);
	Model pawn3("chess_pawn", shaderProgram, "pawn.colour.white.png");
	pawn3.scaleFactor = 0.17;
	pawn3.translate(-4 * squareSize, 0, 0);
	models.push_back(pawn3);
	Model pawn4("chess_pawn", shaderProgram, "pawn.colour.white.png");
	pawn4.scaleFactor = 0.17;
	pawn4.translate(-5 * squareSize, 0, 0);
	models.push_back(pawn4);*/
}

void ChessBoard::draw()
{
	for (Model &m : models) {
		m.draw();
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
