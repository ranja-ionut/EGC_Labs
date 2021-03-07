#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		// TASK 2
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0.5, 1, 1)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0.5, 1, 1)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0.5, 1, 1)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0.5, 1, 1)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			1, 3, 2,	// indices for second triangle
			// TODO: Complete indices data
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4
		};

		// TASK 4
		vector<VertexFormat> vertices2
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)), // 0
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)), // 1
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)), // 2
			VertexFormat(glm::vec3(0.25f, 1, 0.25f), glm::vec3(1, 0, 0.5))  // 3
		};

		vector<unsigned short> indices2 =
		{
			0, 2, 1,
			1, 3, 0,
			2, 0, 3,
			2, 3, 1
		};

		//  TASK 6
		vector<VertexFormat> vertices3
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), // 0
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 1)), // 1
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1)), // 2
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)), // 3
		};

		vector<unsigned short> indices3 =
		{
			0, 1, 2,
			2, 3, 1
		};
		
		// Bonus 2
		vector<VertexFormat> vertices4
		{	
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 1, 0)), // 0 1 - 0 X
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 1)), // 0 2 - 1 X
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1)), // 0 3 - 2 X
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 0)), // 1 1 - 3 X
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0, 1)), // 1 2 - 4 X
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 1, 1)), // 1 3 - 5 X
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 1, 0)), // 2 1 - 6 X
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 1)), // 2 2 - 7 X
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0, 1, 1)), // 2 3 - 8 X
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0)), // 3 1 - 9 X
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0, 1)), // 3 2 - 10 X
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0, 1, 1)), // 3 3 - 11 X
			VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(1, 1, 0)), // 4 1 - 12 X
			VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(1, 0, 1)), // 4 2 - 13 X
			VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(0, 1, 1)), // 4 3 - 14 X
			VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(1, 1, 0)), // 5 1 - 15 X
			VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(1, 0, 1)), // 5 2 - 16 X
			VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(0, 1, 1)), // 5 3 - 17 X
			VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(1, 1, 0)), // 6 1 - 18 X
			VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(1, 0, 1)), // 6 2 - 19 X
			VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(0, 1, 1)), // 6 3 - 20 X
			VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(1, 1, 0)), // 7 1 - 21 X
			VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(1, 0, 1)), // 7 2 - 22 X
			VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(0, 1, 1))  // 7 3 - 23 X
		};

		vector<unsigned short> indices4 =
		{
			0, 6, 3,	// indices for first triangle
			3, 6, 9,	// indices for second triangle
			7, 22, 10,
			7, 19, 22,
			5, 11, 23,
			5, 23, 17,
			18, 12, 21,
			21, 12, 15,
			1, 4, 13,
			4, 16, 13,
			8, 14, 20,
			2, 14, 8
		};

		meshes["cube1"] = new Mesh("generated cube 1");
		meshes["cube1"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		Mesh *cube = CreateMesh("cube3", vertices, indices);

		Mesh *tetr = CreateMesh("tetr", vertices2, indices2);

		Mesh *sq = CreateMesh("sq", vertices3, indices3);

		Mesh* bonus = CreateMesh("bonus", vertices4, indices4);
	}
}

Mesh* Laborator2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	// TASK 3
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// TODO: Enable face culling
	glEnable(GL_CULL_FACE);

	// TODO: Set face custom culling. Use the "cullFace" variable
	glCullFace(cullFace);

	// render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

	// render an object using colors from vertex
	RenderMesh(meshes["cube1"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

	RenderMesh(meshes["cube3"], shaders["VertexColor"], glm::vec3(0, 0.5f, 1), glm::vec3(0.25f));

	RenderMesh(meshes["tetr"], shaders["VertexColor"], glm::vec3(0, 0.5f, 2), glm::vec3(0.25f));

	RenderMesh(meshes["sq"], shaders["VertexColor"], glm::vec3(-2, 0.5f, 1), glm::vec3(0.25f));

	RenderMesh(meshes["bonus"], shaders["VertexColor"], glm::vec3(2, 0.5f, 1), glm::vec3(0.25f));

	// TODO: Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
	// TASK 5
	// TODO: switch between GL_FRONT and GL_BACK culling
	if (key == GLFW_KEY_F2) {
		if (cullFace == GL_FRONT) {
			cullFace = GL_BACK;
		}
		else {
			cullFace = GL_FRONT;
		}
	}

	// Save the state in "cullFace" variable and apply it in the Update() method not here

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

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}
