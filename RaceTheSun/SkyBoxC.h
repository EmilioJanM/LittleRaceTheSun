#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"

#include "Shadern.h"
#include "Camera.h"

class SkyBoxC
{
public:
	SkyBoxC();
	~SkyBoxC();

	void ParentPos(float x, float y, float z);

	float x, y, z;
	unsigned int loadCubemap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}
	std::vector<std::string> faces
	{
		"../Sky/drakeq_rt.tga",
		"../Sky/drakeq_lf.tga",
		"../Sky/drakeq_up.tga",
		"../Sky/drakeq_dn.tga",
		"../Sky/drakeq_ft.tga",
		"../Sky/drakeq_rt.tga"
	};
	float skyboxVertices[108] = {
		// positions          
		-100.f,  100.f, -300,
		-100.f, -100.f, -300,
		100.f, -100.f, -300,
		100.f, -100.f, -300,
		100.f,  100.f, -300,
		-100.f,  100.f, -300,

		-100.f, -100.f,  300,
		-100.f, -100.f, -300,
		-100.f,  100.f, -300,
		-100.f,  100.f, -300,
		-100.f,  100.f,  300,
		-100.f, -100.f,  300,

		100.f, -100.f, -300,
		100.f, -100.f,  300,
		100.f,  100.f,  300,
		100.f,  100.f,  300,
		100.f,  100.f, -300,
		100.f, -100.f, -300,

		-100.f, -100.f,  300,
		-100.f,  100.f,  300,
		100.f,  100.f,  300,
		100.f,  100.f,  300,
		100.f, -100.f,  300,
		-100.f, -100.f,  300,

		-100.f,  100.f, -300,
		100.f,  100.f, -300,
		100.f,  100.f,  300,
		100.f,  100.f,  300,
		-100.f,  100.f,  300,
		-100.f,  100.f, -300,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	unsigned int cubemapTexture = loadCubemap(faces);

	void Init();
	void Update();
	
	unsigned int VAO, VBO, EBO;
	Shader * shaderColor3D = new Shader("Shaders/SkyBox.vs", "Shaders/SkyBox.fs");

};

