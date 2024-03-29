// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include "Mesh.h"

#include "VertexArray.h"

Mesh::Mesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<Index> indices)
{
	float xMax = vertices.at(0).x;
	float xMin = vertices.at(0).x;
	float yMax = vertices.at(0).y;
	float yMin = vertices.at(0).y;
	float zMax = vertices.at(0).z;
	float zMin = vertices.at(0).z;

	for (Index i : indices) {
		Vertex v;
		v.position = vertices.at(i.vIndex - 1);
		v.uv = uvs.at(i.vtIndex - 1);
		v.normal = normals.at(i.vnIndex - 1);
		this->vertices.push_back(v);
		if (v.position.x > xMax) {
			xMax = v.position.x;
		} else if (v.position.x < xMin) {
			xMin = v.position.x;
		}
		if (v.position.y > yMax) {
			yMax = v.position.y;
		}
		else if (v.position.y < yMin) {
			yMin = v.position.y;
		}
		if (v.position.z > zMax) {
			zMax = v.position.z;
		}
		else if (v.position.z < zMin) {
			zMin = v.position.z;
		}
	}
	
	center = vec3((xMin + xMax) / (float)2, (yMin + yMax) / (float)2, (zMin + zMax) / (float)2);
	boundingBox.x = xMax - xMin;
	boundingBox.y = yMax - yMin;
	boundingBox.z = zMax - zMin;
	boundingBox.xMax = xMax;
	boundingBox.xMin = xMin;
	boundingBox.yMax = yMax;
	boundingBox.yMin = yMin;
	boundingBox.zMax = zMax;
	boundingBox.zMin = zMin;
	va = new VertexArray(this->vertices);

}

Mesh::~Mesh()
{
}

void Mesh::draw()
{
	va->draw();
}
