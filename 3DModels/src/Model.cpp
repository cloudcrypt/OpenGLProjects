#include "Model.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Mesh.h"

using glm::vec2;
using glm::vec3;
using std::vector;

Model::Model(string objFile, const ShaderProgram &sp): shaderProgram(sp)
{
	loadModel(objFile);
	setModelMatrix();
}

Model::~Model()
{
}

void Model::draw()
{
	for (Mesh &m : meshes) {
		m.draw();
	}
}

void Model::processKeyboard(int key)
{
	switch (key) {
		case GLFW_KEY_UP:
			scaleFactor *= 1.1;
			setModelMatrix();
			break;
		case GLFW_KEY_DOWN:
			scaleFactor *= 0.9;
			setModelMatrix();
			break;
		case GLFW_KEY_D:
			yaw++;
			setModelMatrix();
			break;
		case GLFW_KEY_A:
			yaw--;
			setModelMatrix();
			break;
		case GLFW_KEY_W:
			pitch--;
			setModelMatrix();
			break;
		case GLFW_KEY_S:
			pitch++;
			setModelMatrix();
			break;
		case GLFW_KEY_E:
			roll--;
			setModelMatrix();
			break;
		case GLFW_KEY_Q:
			roll++;
			setModelMatrix();
			break;
	}
}


void Model::setScaling()
{

}

void Model::setPitch()
{
}

void Model::setYaw()
{
}

void Model::setRoll()
{
}

void Model::setModelMatrix()
{
	modelMatrix = mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)roll), vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)yaw), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians((float)pitch), vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, vec3(scaleFactor, scaleFactor, scaleFactor));
	modelMatrix = glm::translate(modelMatrix, vec3(-meshes.at(0).center.x, -meshes.at(0).center.y, -meshes.at(0).center.z));
	shaderProgram.bind();
	shaderProgram.setMat4("model", modelMatrix);
}

void Model::setMaterial()
{
	shaderProgram.bind();
	shaderProgram.setFloat("material.specularExp", material.specularExp);
	shaderProgram.setVec3("material.specular", material.specular);
	shaderProgram.setVec3("material.diffuse", material.diffuse);
	shaderProgram.setVec3("material.ambient", material.ambient);
}

void Model::loadModel(string objFile)
{
	std::ifstream f(objFile);
	if (!f)
	{
		std::cerr << "Error opening file " << objFile << std::endl;
		exit(1);
	}
	string line;
	string mtlFile;
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<Index> indices;
	while (std::getline(f, line))
	{
		if (line.substr(0, 1) == "#")
			continue;
		else if (line.substr(0, 6) == "mtllib") {
			mtlFile = line.substr(7, string::npos);
		}
		else if (line.substr(0, 2) == "v ") {
			vec3 vertex;
			sscanf_s(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		} else if (line.substr(0, 2) == "vt") {
			vec2 uv;
			sscanf_s(line.c_str(), "vt %f %f", &uv.x, &uv.y);
			uvs.push_back(uv);
		} else if (line.substr(0, 2) == "vn") {
			vec3 normal;
			sscanf_s(line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		} else if (line.substr(0, 2) == "f ") {
			vector<string> indexStrs;
			int currentStart = 2;
			int nextSpace;
			while ((nextSpace = line.find_first_of(' ', currentStart)) != string::npos)
			{
				indexStrs.push_back(line.substr(currentStart, nextSpace - currentStart));
				currentStart = nextSpace + 1;
			}
			indexStrs.push_back(line.substr(currentStart, string::npos));
			for (string indexStr : indexStrs) {
				Index i;
				sscanf_s(indexStr.c_str(), "%d/%d/%d", &i.vIndex, &i.vtIndex, &i.vnIndex);
				indices.push_back(i);
			}
		}
	}
	if (mtlFile != "") {
		loadMaterial(mtlFile);
	}
	this->meshes.push_back(Mesh(vertices, uvs, normals, indices));
}

void Model::loadMaterial(string mtlFile)
{
	string mtlPath = "objs/" + mtlFile;
	std::ifstream f(mtlPath);
	if (!f)
	{
		std::cerr << "Error opening file " << mtlFile << std::endl;
		exit(1);
	}
	string line;
	while (std::getline(f, line))
	{
		if (line.substr(0, 1) == "#")
			continue;
		else if (line.substr(0, 2) == "Ns") {
			float specularExp;
			sscanf_s(line.c_str(), "Ns %f", &specularExp);
			material.specularExp = specularExp;
		}
		else if (line.substr(0, 2) == "Ks") {
			vec3 specular;
			sscanf_s(line.c_str(), "Ks %f %f %f", &specular.x, &specular.y, &specular.z);
			material.specular = specular;
		}
		else if (line.substr(0, 2) == "Kd") {
			vec3 diffuse;
			sscanf_s(line.c_str(), "Kd %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
			material.diffuse = diffuse;
		}
		else if (line.substr(0, 2) == "Ka") {
			vec3 ambient;
			sscanf_s(line.c_str(), "Ka %f %f %f", &ambient.x, &ambient.y, &ambient.z);
			material.ambient = ambient;
		}
	}
	setMaterial();
}
