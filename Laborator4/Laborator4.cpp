#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f,-1.5f);
	modelMatrix *= Transform3D::Translate(translate.x, translate.y, translate.z);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	
	// BONUSURILE
	Bonus1(deltaTimeSeconds);
	Bonus2(deltaTimeSeconds);
}

void Laborator4::Bonus1(float deltaTimeSeconds) {
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(3*move.x, 0.5f + abs(sin(angle)), 0);
	modelMatrix *= Transform3D::RotateOZ(angle);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(3 * move.x, 0.5f + abs(sin(angle)), 0);
	modelMatrix *= Transform3D::RotateOZ(angle);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(45));
	modelMatrix *= Transform3D::Translate(0.2f, 0, 0.5f);
	modelMatrix *= Transform3D::Scale(0.1f, 0.5f, 0.1f);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(3 * move.x, 0.5f + abs(sin(angle)), 0);
	modelMatrix *= Transform3D::RotateOZ(angle);
	modelMatrix *= Transform3D::RotateOZ(-RADIANS(45));
	modelMatrix *= Transform3D::Translate(-0.2f, 0, 0.5f);
	modelMatrix *= Transform3D::Scale(0.1f, 0.5f, 0.1f);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
}

void Laborator4::Bonus2(float deltaTimeSeconds) {
	angle += deltaTimeSeconds;
	move += glm::vec3(deltaTimeSeconds) * 0.25f;

	// soare
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0 + move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// pamant
	modelMatrix = glm::mat4(1);
	
	modelMatrix *= Transform3D::Translate(move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle * 2);
	modelMatrix *= Transform3D::Translate(-move.x, -0.5f - move.y, 0 - move.z);

	modelMatrix *= Transform3D::Translate(2 + move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle * 2);
	modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// luna
	modelMatrix = glm::mat4(1);
	
	modelMatrix *= Transform3D::Translate(move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle * 2);
	modelMatrix *= Transform3D::Translate(-move.x, -0.5f - move.y, 0 - move.z);

	
	modelMatrix *= Transform3D::Translate(2 + move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle * 4);
	modelMatrix *= Transform3D::Translate(-2 -move.x, -0.5f - move.y, 0 - move.z);

	modelMatrix *= Transform3D::Translate(3 + move.x, 0.5f + move.y, 0 + move.z);
	modelMatrix *= Transform3D::RotateOY(angle * 4);
	modelMatrix *= Transform3D::Scale(0.25f, 0.25f, 0.25f);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// TASK 3

	// TODO
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		glm::vec3 offset = glm::vec3(0);

		if (window->KeyHold(GLFW_KEY_W)) {
			offset -= glm::vec3(0, 0, 1);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			offset -= glm::vec3(1, 0, 0);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			offset += glm::vec3(0, 0, 1);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			offset += glm::vec3(1, 0, 0);
		}

		if (window->KeyHold(GLFW_KEY_R)) {
			offset -= glm::vec3(0, 1, 0);
		}

		if (window->KeyHold(GLFW_KEY_F)) {
			offset += glm::vec3(0, 1, 0);
		}

		if (glm::length(offset) > 0) {
			offset = deltaTime * glm::normalize(offset);
		}

		translate += offset;
	}

	if (window->KeyHold(GLFW_KEY_1)) {
		scaleX += deltaTime;
		scaleY += deltaTime;
		scaleZ += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_2)) {
		scaleX -= deltaTime;
		scaleY -= deltaTime;
		scaleZ -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_3)) {
		angularStepOX -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_4)) {
		angularStepOX += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_5)) {
		angularStepOY -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_6)) {
		angularStepOY += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_7)) {
		angularStepOZ -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_8)) {
		angularStepOZ += deltaTime;
	}
}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
