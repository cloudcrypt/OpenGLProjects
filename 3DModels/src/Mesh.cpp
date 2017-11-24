#include "Mesh.h"

#include "VertexArray.h"

Mesh::Mesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<Index> indices)
{
	//unsigned int currentValue = 0;
	//std::map<Vertex, int>::iterator it;

	for (Index i : indices) {
		Vertex v;
		v.position = vertices.at(i.vIndex - 1);
		v.uv = uvs.at(i.vtIndex - 1);
		v.normal = normals.at(i.vnIndex - 1);
		this->vertices.push_back(v);
		/*it = indexMap.find(v);
		if (it == indexMap.end()) {
			indexMap[v] = currentValue;
			this->vertices.push_back(v);
			this->indices.push_back(currentValue);
			currentValue++;
		} else {
			this->indices.push_back(it->second);
		}*/
	}

	va = new VertexArray(this->vertices);

}

Mesh::~Mesh()
{
}

void Mesh::draw()
{
	va->draw();
}
