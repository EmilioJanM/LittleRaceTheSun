#define MAINCAMERA_DEF

#include "main.h"	//MOVE WITH A, D

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void processInputCam(GLFWwindow *window, float &var, Player &player);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

std::vector<Pyramid*> pyrVec;
std::vector<Rect*> rectVec;

int main()
{
	//MOVE WITH A, D
	int width, height, nrChannels;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RaceDaSun", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	srand(time(NULL));

	//Camera
	Camera &cam = MainCamera;
	cam.SetPos(0, 1, 9); cam.SetRot(5, 1, 0, 0);

	


	//Init Geometry
	Plane *plane = new Plane(0, 2, 0); plane->Init();
	Player *player = new Player(0, -1, 0); player->Init();

	float var = 0;
	

	for (Rect *rec : rectVec)
		rec->Init();
	for (Pyramid *pyr : pyrVec)
		pyr->Init();

	float timer = 0;
	float timerP = 0;
	bool play = true;
	int score = 0;

	//SkyBox
	SkyBoxC *box = new SkyBoxC(); box->Init();
	
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window) && play)
	{	
		//MOVE WITH A, D

		// input
		// -----
		processInputCam(window, var, *player);

		// render
		// ------
		glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		plane->ParentPos(cam.cameraPos.x, -2, cam.cameraPos.z);
		box->ParentPos(cam.cameraPos.x, 0, cam.cameraPos.z);
		player->Parent(cam.cameraPos.x, -1 ,cam.cameraPos.z-9);
															
		//Spawn objects
		if (rectVec.size() < 200) {
			int lado = rand() % 2;
			Rect *rec;
			if (timer > 0.3f) {
				if (lado == 0)
					rec = new Rect(cam.cameraPos.x + ((rand() % 10) * rand() % 150), -2, cam.cameraPos.z - 300, (rand() % 25)+5);
				else
					rec = new Rect(cam.cameraPos.x - ((rand() % 10) * rand() % 150), -2, cam.cameraPos.z - 300, (rand() % 25)+5);
				rectVec.push_back(rec);
				timer = 0;
			}
		}
		if (pyrVec.size() < 50) {
			int lado = rand() % 2;
			Pyramid *pyr;
			if (timerP > 1.f) {
				if (lado == 0)
					pyr = new Pyramid(cam.cameraPos.x + ((rand() % 10) * rand() % 150), -2, cam.cameraPos.z - 300);
				else
					pyr = new Pyramid(cam.cameraPos.x - ((rand() % 10) * rand() % 150), -2, cam.cameraPos.z - 300);
				pyrVec.push_back(pyr);
				timerP = 0;
			}
		}

		//Update, Collisions
		std::vector<Rect*>::iterator rectIt;
		if (rectVec.size() != 1) {
			for (rectIt = rectVec.begin(); rectIt != rectVec.end(); ++rectIt) {
				if (!(*rectIt)->init)
					(*rectIt)->Init();
				(*rectIt)->shaderColor3D->setFloat("camPos", (player->z - (*rectIt)->z) / 350);
				(*rectIt)->Update();
				if (player->z - (*rectIt)->z < -1) {
					delete *rectIt;
					rectVec.erase(rectIt);
					rectIt = rectVec.begin();
				}
				if (abs(player->z - (*rectIt)->z) < 1 && abs(player->x - (*rectIt)->x) < 1)
					play = false;
			}
		}

		std::vector<Pyramid*>::iterator pyrIt;
		if (pyrVec.size() != 1) {
			for (pyrIt = pyrVec.begin(); pyrIt != pyrVec.end(); ++pyrIt) {
				if (!(*pyrIt)->init)
					(*pyrIt)->Init();
				(*pyrIt)->shaderColor3D->setFloat("camPos", (player->z - (*pyrIt)->z) / 500);
				(*pyrIt)->Update();
				if (cam.cameraPos.z - (*pyrIt)->z < -1) {
					delete *pyrIt;
					pyrVec.erase(pyrIt);
					pyrIt = pyrVec.begin();
				}
				if (abs(player->z - (*pyrIt)->z) < 2.5f && abs(player->x - (*pyrIt)->x) < 2.5f) {
					score += 1000;
					std::cout << "Score: " << score << "!" << std::endl;
					delete *pyrIt;
					pyrVec.erase(pyrIt);
					pyrIt = pyrVec.begin();
				}
			}
		}



		box->Update();
		plane->Update();
		player->Update();

		timer += 0.3f;
		timerP += 0.2f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void processInputCam(GLFWwindow *window, float &var, Player &player)
{
	Camera &cam = MainCamera;
	float cameraSpeed = 1.f; //velocity
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraSpeed = 0.4;
	cam.cameraPos += cameraSpeed * cam.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.cameraPos -= glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * (cameraSpeed / 3);
		if (player.rot < 35)
			player.rot += 0.7f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.cameraPos += glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * (cameraSpeed / 3);
		if (player.rot > -35)
			player.rot -= 0.7f;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (player.rot != 0) {
		if (player.rot > 0) 
			player.rot -= 0.3f;
		else
			player.rot += 0.3f;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
