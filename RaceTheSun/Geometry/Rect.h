#pragma once

#include <iostream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Shadern.h"
#include "../Camera.h"

class Rect
{
public:
	Rect(int _x, int _y, int _z, const float _rand);
	~Rect();

	int x, y, z;
	bool init = false;
	Shader * shaderColor3D = new Shader("Shaders/ColorFade.vs", "Shaders/ColorFade.fs");

	void Init();
	void Update();

private:
	unsigned int VAO, VBO, EBO;
	const float rand;


	float vertices[96]{
		 1.f,  1.f  * rand,  0.5f, 0.5f, 0.5f, 0.5f,  //front
		-1.f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,
		 1.f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,
		-1.f,  1.f * rand,  0.5f, 0.5f, 0.5f, 0.5f,

		 1.f,  1.f * rand,   0.5f, 0.2f, 0.2f, 0.2f, //right
		 1.f, -0.5f, -1.f, 0.2f, 0.2f, 0.2f,
		 1.f, -0.5f,  0.5f, 0.2f, 0.2f, 0.2f,
		 1.f,  1.f * rand,  -1.f, 0.2f, 0.2f, 0.2f,
		 
		-1.f,  1.f * rand,   0.5f, 0.2f, 0.2f, 0.2f, //left
		-1.f, -0.5f, -1.f, 0.2f, 0.2f, 0.2f,
		-1.f, -0.5f,  0.5f, 0.2f, 0.2f, 0.2f,
		-1.f,  1.f * rand,  -1.f, 0.2f, 0.2f, 0.2f,

		-1.f,  1.f * rand,  0.5f, 0.2f, 0.2f, 0.2f, //top
		-1.f,  1.f * rand, -0.5f, 0.2f, 0.2f, 0.2f,
		 1.f,  1.f * rand, -0.5f, 0.2f, 0.2f, 0.2f,
		 1.f,  1.f * rand,  0.5f, 0.2f, 0.2f, 0.2f
	};
	unsigned int indices[24]{
		0,1,2,
		3,1,0,
		4,5,6,
		7,5,4,
		8,9,10,
		11,9,8,
		12,13,14,
		12,14,15
	};
};

