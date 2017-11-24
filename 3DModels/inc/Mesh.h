#pragma once

#include <vector>
#include <map>
#include "glm/glm.hpp"

//#include "VertexArray.h"

using glm::vec2;
using glm::vec3;
using std::vector;

class VertexArray;

struct Index {
	int vIndex;
	int vtIndex;
	int vnIndex;
};

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;

	bool operator==(const Vertex &v2) const {
		return ((position.x == v2.position.x) && (position.y == v2.position.y) && (position.z == v2.position.z))
		&& ((normal.x == v2.normal.x) && (normal.y == v2.normal.y) && (normal.z == v2.normal.z))
		&& ((uv.x == v2.uv.x) && (uv.y == v2.uv.y));
	}

	//bool operator<(const Vertex &v2) const {
	//	/*return ((position.x < v2.position.x) && (position.y < v2.position.y) && (position.z < v2.position.z))
	//		&& ((normal.x < v2.normal.x) && (normal.y < v2.normal.y) && (normal.z < v2.normal.z))
	//		&& ((uv.x < v2.uv.x) && (uv.y < v2.uv.y));*/
	//	if ((position.x == v2.position.x) && (position.y == v2.position.y) && (position.z == v2.position.z)) {
	//		if ((normal.x == v2.normal.x) && (normal.y == v2.normal.y) && (normal.z == v2.normal.z)) {
	//			return ((uv.x < v2.uv.x) || (uv.y < v2.uv.y));
	//		} else {
	//			return ((normal.x < v2.normal.x) || (normal.y < v2.normal.y) || (normal.z < v2.normal.z));
	//		}
	//	} else {
	//		return ((position.x < v2.position.x) || (position.y < v2.position.y) || (position.z < v2.position.z));
	//	}
	//}
};

class Mesh
{
public:
	Mesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<Index> indices);
	~Mesh();
	void draw();
private:
	vector<Vertex> vertices;
	VertexArray* va;
	//vector<unsigned int> indices;
	//std::map<Vertex, int> indexMap;
};

