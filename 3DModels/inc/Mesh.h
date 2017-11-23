#pragma once

#include <vector>
#include "glm/glm.hpp"

using glm::vec3;
using glm::mat4;

class Mesh
{
public:
	Mesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals);
	~Mesh();
};

