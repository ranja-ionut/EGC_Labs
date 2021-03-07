#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	angularStep = 0;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* luna = Object2D::CreateSquare("luna", corner, squareSide / 4, glm::vec3(0.5f, 0.5f, 0.5f), true);
	AddMeshToList(luna);

	Mesh* soare = Object2D::CreateSquare("soare", corner, squareSide, glm::vec3(1, 1, 0), true);
	AddMeshToList(soare);

	Mesh* pamant = Object2D::CreateSquare("pamant", corner, squareSide / 2, glm::vec3(0, 0, 1), true);
	AddMeshToList(pamant);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TASK 3
	
	// TODO: update steps for translation, rotation, scale, in order to create animations
	translateX += deltaTimeSeconds * 32.7f;
	translateY += deltaTimeSeconds * 25.7f * reverseY;
	scaleX += deltaTimeSeconds * 0.5f * reverseS;
	scaleY += deltaTimeSeconds * 0.5f * reverseS;
	angularStep += deltaTimeSeconds * 0.7f;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, 250);
	modelMatrix *= Transform2D::Translate(50, 50);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Translate(-50, -50);

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(400, 250);
	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	modelMatrix *= Transform2D::Translate(0, translateY);

	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(650, 250);
	modelMatrix *= Transform2D::Translate(50, 50);
	modelMatrix *= Transform2D::Rotate(-angularStep);
	modelMatrix *= Transform2D::Translate(-50, -50);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	if (scaleX < 0.5 || scaleX > 3) {
		reverseS = -reverseS;
	}

	if (translateY > 300 || translateY < 0) {
		reverseY = -reverseY;
	}

	// BONUS

	// soarele
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(250, 250);
	modelMatrix *= Transform2D::Translate(translateX, 0);
	modelMatrix *= Transform2D::Translate(50, 50);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-50, -50);

	RenderMesh2D(meshes["soare"], shaders["VertexColor"], modelMatrix);


	//pamantul
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(275, 275);
	modelMatrix *= Transform2D::Translate(translateX + 300, 0);
	modelMatrix *= Transform2D::Translate(-275, 25);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(275, -25);
	modelMatrix *= Transform2D::Translate(25, 25);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-25, -25);

	RenderMesh2D(meshes["pamant"], shaders["VertexColor"], modelMatrix);

	// luna
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(287.5f, 287.5f);
	modelMatrix *= Transform2D::Translate(translateX + 400, 0);
	modelMatrix *= Transform2D::Translate(-387.5f, 12.5f);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(387.5f, -12.5f);

	modelMatrix *= Transform2D::Translate(-87.5f, 12.5f);
	modelMatrix *= Transform2D::Rotate(2 * angularStep);
	modelMatrix *= Transform2D::Translate(87.5f, -12.5f);

	modelMatrix *= Transform2D::Translate(12.5f, 12.5f);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-12.5f, -12.5f);


	RenderMesh2D(meshes["luna"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
