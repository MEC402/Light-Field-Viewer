// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


#include"Renderer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"Plane.h"
#include"Camera.h"
#include"CameraPlane.h"

#include "vendor/Imgui/imgui.h"
#include "vendor/Imgui/imgui_impl_glfw.h"
#include "vendor/Imgui/imgui_impl_opengl3.h"

bool processInput(GLFWwindow* window);
glm::vec3 rayCast(float* vertecies, int vertexCount, glm::vec3 p0, glm::vec3 n, glm::vec3 eye);


Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

unsigned int eye2CameraPlaneDist = 10;
unsigned int eye2ImagePlaneDist = 3;

glm::vec3 cameraPlaneCenter(camera.Position.x, camera.Position.y, camera.Position.z - eye2CameraPlaneDist);
glm::vec3 imagePlaneCenter(camera.Position.x, camera.Position.y, camera.Position.z - eye2ImagePlaneDist);
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));


int main() {

	// *********************************************************************************
	// *************************** Creating a Window ***********************************
	// *********************************************************************************

	GLFWwindow* window;
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, "Light Field Viewer", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// *********************************************************************************
	// ********************** Init OpenGL Context and GLEW *****************************
	// *********************************************************************************

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error with initializing GlEW. Make sure that glew is after a valid opengl context.\n";
	}

	std::cout << "OpenGL context created and the version is: " << glGetString(GL_VERSION) << std::endl;

	//Enable Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH);


	// *********************************************************************************
	// ****************************** Static Data **************************************
	// *********************************************************************************

	int r = 10;
	int c = 10;

	Plane p;

	//float* v = p.generateVertecies(r, c, camera.Position.z-eye2ImagePlaneDist);
	float* v = p.generateVertecies(r, c, glm::vec3(0, 0, -20));
	unsigned int* idx = p.generateIndecies(r, c);
	unsigned int vertexCount = r * c * 9;
	unsigned int indCount = (r - 1) * (c - 1) * 2 * 3;

	//unsigned int vertexCount = 4*4;
	//unsigned int indCount = 6;

	/*float positions[] = {
		-512.0f , -512.0f , -20.0f ,
		512.0f  , -512.0f , -20.0f ,
		-512.0f  ,  512.0f , -20.0f , 
		512.0f ,  512.0f , -20.0f
	};*/

	/*float positions[] = {
		0.0f , 0.0f , 0.0f , 0.0f,
		1.0f  , 0.0f , 1.0f , 0.0f,
		0.0f  ,  1.0f , 1.0f , 1.0f,
		1.0f ,  1.0f , 0.0f , 1.0f
	};

	unsigned int indices[] = {
		0,2,1,
		2,3,1
	};*/

	VertexBufferLayout layout;
	layout.push<float>(3);// 3D position values
	layout.push<float>(2);// 2D texture values
	layout.push<float>(4);// 4D camera index
	IndexBuffer ib(idx, indCount);

	VertexArray va;
	VertexBuffer vb(v, vertexCount * sizeof(float));
	va.addBuffer(vb, layout);


	// *********************************************************************************
	// ******************************* Math Stuff **************************************
	// *********************************************************************************

	//glm::mat4 view=gluLookAt(eye.x,eye.y,eye.z,0,0,0,up.x,up.y,up.z);

	//glm::mat4 proj = glm::ortho(0.0f,(float)windowWidth,0.0f, (float)windowHeight,-1.0f,1.0f);
	//glm::mat4 proj = glm::ortho(0.0f, r*2.0f, 0.0f, c*2.0f, -1.0f, 1.0f);
	std::cout << "Camera Zoom:" << camera.Zoom;
	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	// *********************************************************************************
	// *************************** Attaching Shaders ***********************************
	// *********************************************************************************

	Shader shader("res/shaders/Basic.shader"); //parse, compile and link shaders
	shader.bind();

	// *********************************************************************************
	// ************************** Attaching Textures ***********************************
	// *********************************************************************************

	Texture texture0("res/textures/headlf.jpg");
	texture0.bind(0);
	shader.setUniform1i("u_texture0",0);//number here should match the texture binding slot specified in bind texture

	Texture texture1("res/textures/lobbylf.jpg");
	texture1.bind(1);
	shader.setUniform1i("u_texture1", 1);//number here should match the texture binding slot specified in bind texture

	Texture texture2("res/textures/sanmiguellf.jpg");
	texture2.bind(2);
	shader.setUniform1i("u_texture2", 2);//number here should match the texture binding slot specified in bind texture

	Texture texture3("res/textures/trainlf.jpg");
	texture3.bind(3);
	shader.setUniform1i("u_texture0", 3);//number here should match the texture binding slot specified in bind texture


	shader.setUniform1i("u_numberOfCameras", 17);

	shader.setUniformVec3f("u_cameraPlaneCenter", 0, 0, -100);
	shader.setUniformVec3f("u_cameraPlaneNormal", 0, 0, 1);
	shader.setUniform1i("u_cameraPlaneSize", 360);

	shader.setUniformVec3f("u_cameraPosition", 0, 0, 0);
	shader.setUniform1f("u_cameraPlaneImagePlaneDist", -10);

	shader.setUniformVec3f("u_focalPlaneCenter", 0, 0, -200);
	shader.setUniformVec3f("u_focalPlaneNormal", 0, 0, 1);
	shader.setUniform1i("u_focalPlaneSize", 300);


	



	/*shader.setUniform1f("size", 3600 / 9);
	shader.setUniform1i("imageSize", 3600 / 9);

	shader.setUniform1f("u_numberOfCameras", 9);
	shader.setUniform1f("imagePlaneZ", -5);

	shader.setUniformVec3f("cam_pos", 0, 0, 0);

	shader.setUniformVec2f("min_uv", -100, -100);
	shader.setUniformVec2f("max_uv", 100, 100);

	shader.setUniformVec3f("u_cameraPlaneCenter", 0, 0, 10);
	shader.setUniformVec3f("u_cameraPlaneNormal", 0, 0, -1);

	shader.setUniform1i("debugInt", 10);
	shader.setUniform1i("sampleMode", 2);*/


	// *********************************************************************************
	// ******************************** Uniforms ***************************************
	// *********************************************************************************

	//shader.setUniform4f("u_color", 0.8f, 0.3f, 0.5f, 1.0f);

	// *********************************************************************************
	// ************************* Clear Previous States *********************************
	// *********************************************************************************

	//va.unbind();
	//vb.unbind();
	//ib.unbind();
	shader.unbind();

	Renderer renderer;

	// *********************************************************************************
	// ************************* Initialize ImGUI *********************************
	// *********************************************************************************

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// *********************************************************************************
	// ****************************** Render Loop **************************************
	// *********************************************************************************
	{
		glm::vec3 translate(0.0f, 0.0f, 0.0f);
		float dist = 100;
		float focalDist = 200;

		int camIndU = 0;
		int camIndV = 0;
		shader.setUniform1i("tn", 5);


		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (processInput(window)) {
				shader.setUniformVec3f("u_cameraPosition", camera.Position.x, camera.Position.y, camera.Position.z);
				//rayCast(v, vertexCount, camera.Front, camera.Position- camera.Front, camera.Position);
			}

			va.bind();

			texture0.bind(0);
	

			renderer.clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			view = glm::translate(glm::mat4(1.0f), translate);
			//view = camera.GetViewMatrix();
			glm::mat4 mvp = proj * view * model;
			shader.setUniformMat4f("u_MVP", mvp);

			int l = vertexCount - 1;

			/*glm::vec4 fv = glm::vec4(v[0], v[1], v[2],1);
			glm::vec4 lv = glm::vec4(v[63], v[64], v[65], 1);

			glm::vec4 fvW = mvp * fv;
			glm::vec4 lvW = mvp * lv;

			float dx = (fvW.x - lvW.x) * (fvW.x - lvW.x);
			float dy = (fvW.y - lvW.y) * (fvW.y - lvW.y);
			float dz = (fvW.z - lvW.z) * (fvW.z - lvW.z);

			float ImageSize = sqrt(dx + dy + dz);

			shader.setUniform1f("u_imagePlaneSize", ImageSize);

			std::cout << "fv  :" << fv.x << fv.y << fv.z << "\n";
			std::cout << "lv  :" << lv.x << lv.y << lv.z << "\n";

			std::cout<<"fvW   :" << fvW.x << fvW.y << fvW.z << "\n";
			std::cout << "lvW   :" << lvW.x << lvW.y << lvW.z << "\n";

			std::cout << ImageSize << "\n";*/
			




			shader.bind();


			renderer.draw(va, ib, shader);




			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Control Panel");                          // Create a window
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				//ImGui::Checkbox("Another Window", &show_another_window);

				//ImGui::SliderFloat("Camera x", &translate.x, 0.0f, windowWidth);
				//ImGui::SliderFloat("Camera y", &translate.y, 0.0f, windowHeight);
				ImGui::SliderFloat("distCameraPlane", &dist, 0.0f,1000.0f);
				shader.setUniformVec3f("u_cameraPlaneCenter", 0, 0, dist);

				ImGui::SliderFloat("Focal dist", &focalDist, 0.0f, 1000.0f);
				shader.setUniformVec3f("u_focalPlaneCenter", 0, 0, focalDist);

				//ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("0")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 0);
				}
				ImGui::SameLine();
				if (ImGui::Button("1")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 1);
				}
				ImGui::SameLine();
				if (ImGui::Button("2")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 2);
				}
				ImGui::SameLine();
				if (ImGui::Button("3")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 3);
				}
				ImGui::SameLine();
				if (ImGui::Button("4")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 4);
				}
				ImGui::SameLine();
				if (ImGui::Button("5")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					shader.setUniform1i("tn", 5);
				}


				if (ImGui::Button("head")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					texture0.bind(3);
				}
				ImGui::SameLine();
				if (ImGui::Button("lobby")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					texture1.bind(3);
				}
				ImGui::SameLine();
				if (ImGui::Button("green")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					texture2.bind(3);
				}
				ImGui::SameLine();
				if (ImGui::Button("pots")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
					texture3.bind(3);
				}
				




				//ImGui::SameLine();
				//ImGui::Text("counter = %d", counter);

				ImGui::End();
			}


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}


	// *********************************************************************************
	// ************************* Last Minuet Clean Up **********************************
	// *********************************************************************************

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}




bool processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return false;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

		camera.ProcessKeyboard(FORWARD, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(UP, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(DOWN, deltaTime);
		return true;
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		camera.printCameraInformation();
		return false;
	}

	// *********************************************************************************
	// ************************* Move Image Plane **********************************
	// *********************************************************************************

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		model=glm::translate(model, glm::vec3(0, 0.5, 0));
		return false;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		model = glm::translate(model, glm::vec3(0, -0.5, 0));
		return false;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		model = glm::translate(model, glm::vec3(-0.5, 0, 0));
		return false;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		model = glm::translate(model, glm::vec3(0.5, 0, 0));
		return false;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		model = glm::translate(model, glm::vec3(0, 0, -0.5));
		return false;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		model = glm::translate(model, glm::vec3(0, 0, 0.5));
		return false;
	}


	return false;

}

