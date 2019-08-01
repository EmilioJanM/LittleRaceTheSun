#pragma once

#include <iostream>
#include <string>

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shadern.h"
#include "Camera.h"

class Player
{
public:
	Player(int _x, int _y, int _z);
	~Player();

	float x, y, z, rot;
	bool init = false;
	Shader * shaderColor3D = new Shader("Shaders/Player.vs", "Shaders/Player.fs");

	void Init();
	void Update();
	void Parent(float x, float y, float z);

private:
	unsigned int VAO, VBO, EBO;

	float vertices[18]{
		0.0f,  0.5f,  -1.5f, 0.0f, 0.0f, 1.f,  //front
		-1.f, 0.5f, 1.5f, 0.0f, 0.0f, 0.3f,
		1.f,  0.5f ,  1.5f, 0.0f, 0.0f, 0.3f
	};
	unsigned int indices[3]{
		0,1,2
	};
};

