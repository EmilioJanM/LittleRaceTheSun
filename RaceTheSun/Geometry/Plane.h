#pragma once

#include <iostream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Shadern.h"
#include "../Camera.h"

class Plane
{
public:
	Plane(int _x, int _y, int _z);
	~Plane();
	int x, y, z;

	void Init();
	void Update();
	void ParentPos(int x, int y, int z);
	
private:
	Shader * shaderColor3D = new Shader("Shaders/Color3D.vs", "Shaders/Color3D.fs");

	float vertices[24]{
		-30.f,  0.f,  10.f, 0.9f, 0.0f, 0.0f,
		-200.f,  0.f, -300.f, 0.3f, 0.0f, 0.0f,
		 200.f,  0.f, -300.f, 0.3f, 0.0f, 0.0f,
		 30.f,  0.f,  10.f, 0.9f, 0.0f, 0.0f
		 
	};
	unsigned int indices[6]{
		0,1,2,
		0,2,3
	};

	unsigned int VAO, VBO, EBO;
};

