#pragma once

#include <iostream>
#include <string>

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Shadern.h"
#include "../Camera.h"

class Pyramid
{
public:
	Pyramid(int _x, int _y, int _z);
	~Pyramid();

	int x, y, z;
	bool init = false;
	Shader * shaderColor3D = new Shader("Shaders/ColorFade.vs", "Shaders/ColorFade.fs");

	void Init();
	void Update();

private:
	unsigned int VAO, VBO, EBO;

	float vertices[56]{
		0.0f,  6.f,  0.0f, 0.0f, 0.9f, 0.0f,  //front
		-2.5f, -0.5f, 2.5f, 0.0f, 0.9f, 0.0f,
		2.5f, -0.5f ,  2.5f, 0.0f, 0.9f, 0.0f,

		0.0f,  6.f,  0.0f, 0.0f, 0.5f, 0.0f, //left
		-2.5f, -0.5f, 2.5f, 0.0f, 0.5f, 0.0f,
		-2.5f, -0.5f,-2.5f, 0.0f, 0.5f, 0.0f,

		0.0f,  6.f,  0.0f, 0.0f, 0.5f, 0.0f, //right
		2.5f, -0.5f, -2.5f, 0.0f, 0.5f, 0.0f,
		2.5f, -0.5f,  2.5f, 0.0f, 0.5f, 0.0f
	};
	unsigned int indices[9]{
		0,1,2,
		3,4,5,
		6,7,8
	};

	
	
};

