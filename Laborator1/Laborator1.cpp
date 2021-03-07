#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* box = new Mesh("box");
		box->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[box->GetMeshID()] = box;

		Mesh* teapot = new Mesh("teapot");
		teapot->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[teapot->GetMeshID()] = teapot;

		Mesh* sphere = new Mesh("sphere");
		sphere->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[sphere->GetMeshID()] = sphere;

		Mesh* plane50 = new Mesh("plane50");
		plane50->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
		meshes[plane50->GetMeshID()] = plane50;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(r, g, b, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// Task 2
	RenderMesh(meshes["teapot"], glm::vec3(7, 0.5f, 0), glm::vec3(3.5f));

	RenderMesh(meshes["sphere"], glm::vec3(0, 0, 0), glm::vec3(1));

	RenderMesh(meshes["plane50"], glm::vec3(-5, 0.5f, 0), glm::vec3(0.02f));

	// Task 4, 5
	RenderMesh(meshes[vec[n]], glm::vec3(x, y, z), glm::vec3(0.4f));

	if (imp < 0) {
		imp = 0;
	}

	if (y < 0) {
		y = 0;
	}

	if (y == 0) {
		y += (2 * imp) * deltaTimeSeconds * speed;
		grav = -1;
	}

	if (y > 0) {
		y += (grav + 2 * imp) * deltaTimeSeconds * speed;

		imp += grav * deltaTimeSeconds * speed;
	}
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	// Task 5
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_W)) {
			z -= deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			z += deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			x -= deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			x += deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			y -= deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			y += deltaTime * 2;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// Task 3
	if (key == GLFW_KEY_F) {
		r = rand() % 11 / 10.f;

		g = rand() % 11 / 10.f;

		b = rand() % 11 / 10.f;
	}

	// Task 4
	if (key == GLFW_KEY_G) {
		n = (n + 1) % vec_cap;
	}

	if (key == GLFW_KEY_SPACE) {
		imp = 1.3f;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
