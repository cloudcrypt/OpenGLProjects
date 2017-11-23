#pragma once

#include <string>

using std::string;

class Model
{
public:
	Model(string objFile);
	~Model();
private:
	void loadModel(string objFile);
};

