﻿#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "glew.h"
#include <glfw3.h>
#include "glut.h"
#include <string>
#include <functional>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "UserInput.h"
#include "Camera.h"
#include "MeshAccess.h"
#include "Light.h"
#include "CubeBackground.h"

#include "DrawContext.h"

#define MODELLOADING 1

GraphicsEngine gDC;

void UpdateRenderMat(GraphicsEngine & ge)
{
	glm::mat4 model = ge.fCamera->GetModel();
	glm::mat4 view = ge.fCamera->GetView();
	glm::mat4 proj = ge.fCamera->GetProj();
	glm::mat4 normalMat = glm::transpose(glm::inverse(view));

	glm::vec3 eyePos = ge.fCamera->GetEyePos();

	ge.fShader->UpdateUniformMat4("Proj", &proj[0][0]);
	ge.fShader->UpdateUniformMat4("View", &view[0][0]);
	ge.fShader->UpdateUniformMat4("Model", &model[0][0]);
	ge.fShader->UpdateUniformMat4("NormalMat", &normalMat[0][0]);
	ge.fShader->UpdateUniform3fv("EyePos", eyePos[0], eyePos[1], eyePos[2]);

	if (ge.fLights) {
		std::tuple<glm::vec3, glm::vec3, glm::vec3> & lightData = ge.fLights->GetLight(0);

		auto pos = std::get<Light::kLightPos>(lightData);

		ge.fShader->UpdateUniform3fv("LightPos", pos[0], pos[1], pos[2]);
	}

}



void Keyboard(unsigned char key, int x, int y)
{
	if (gDC.fInput)
		gDC.fInput->Keyboard(key, x, y);
	//glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	if (gDC.fInput)
		gDC.fInput->KeyboardUp(key, x, y);
	//glutPostRedisplay();
}

void Keyboard(int key, int x, int y)
{
	if (gDC.fInput)
		gDC.fInput->Keyboard(key, x, y);
	//glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (gDC.fInput)
		gDC.fInput->Mouse(button, state, x, y);
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	if (gDC.fInput)
		gDC.fInput->MouseMotion(x, y);
	//glutPostRedisplay();
}


void EndGL()
{
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

}

static const GLfloat g_cube[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

static const GLfloat g_cube_colors[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

static const GLfloat gPlanes[] = {
	-200.f, 0.f, -200.f, // tri1
	200.f, 0.f, -200.f,
	-200.f, 0.f, 200.f,
	200.f, 0.f, 200.f,
};

static const unsigned short gPlaneInds[] = {
	0, 1, 2,
	2, 1, 3
};

static const GLfloat gPlaneNormals[] = {
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
};


void LoadCube(std::vector<glm::vec3> & verts)
{
	for (size_t i = 0; i < sizeof(g_cube) / sizeof(float); i += 3) {
		// is the index correct?
		verts.push_back(glm::vec3(g_cube[i], g_cube[i + 1], g_cube[i + 2]));
	}

	for (size_t i = 0; i < sizeof(g_cube_colors) / sizeof(float); i += 3) {
		// is the index correct?
		gDC.fColors.push_back(glm::vec3(g_cube_colors[i], g_cube_colors[i + 1], g_cube_colors[i + 2]));
	}

	for (size_t i = 0; i < sizeof(g_cube) / sizeof(float) / 3; i++) {
		//gInds.push_back(i);
	}
}


void ActivateMoveIfKeyPressed()
{
	if (gDC.fInput->IsLeftPressed()) {
		gDC.fInput->Move(EDirection::left);
	}

	if (gDC.fInput->IsRightPressed()) {
		gDC.fInput->Move(EDirection::right);
	}

	if (gDC.fInput->IsUpPressed()) {
		gDC.fInput->Move(EDirection::up);
	}

	if (gDC.fInput->IsDownPressed()) {
		gDC.fInput->Move(EDirection::down);
	}

	if (gDC.fInput->IsBackPressed()) {
		gDC.fInput->Move(EDirection::backward);
	}

	if (gDC.fInput->IsForewardPressed()) {
		gDC.fInput->Move(EDirection::forward);
	}
}


void RenderBackground()
{
	const unsigned int kOutColorID = 0;
	const unsigned int kInPosID = 0;
	const unsigned int kInUV = 2;

	float vertices[] = { //interleaved vertex(3) , uv(2)
		// direction is based on the up vector (0,1,0). front is -z direction. At the beginning, camera is facing left.(-x).
		// front
		-1.0f,  1.0f, -1.0f, 0, 1,
		-1.0f, -1.0f, -1.0f, 0, 0,
		1.0f, -1.0f, -1.0f,  1, 0,
		1.0f, -1.0f, -1.0f,  1, 0,
		1.0f,  1.0f, -1.0f,  1, 1,
		-1.0f,  1.0f, -1.0f, 0, 1,

		// left
		-1.0f, -1.0f,  1.0f, 0, 0,
		-1.0f, -1.0f, -1.0f, 1, 0,
		-1.0f,  1.0f, -1.0f, 1, 1,
		-1.0f,  1.0f, -1.0f, 1, 1,
		-1.0f,  1.0f,  1.0f, 0, 1,
		-1.0f, -1.0f,  1.0f, 0, 0,

		// right
		1.0f, -1.0f, -1.0f, 0, 0,
		1.0f, -1.0f,  1.0f, 1, 0,
		1.0f,  1.0f,  1.0f, 1, 1,
		1.0f,  1.0f,  1.0f, 1, 1,
		1.0f,  1.0f, -1.0f, 0, 1,
		1.0f, -1.0f, -1.0f, 0, 0,

		// back
		-1.0f, -1.0f,  1.0f, 1, 0,
		-1.0f,  1.0f,  1.0f, 1, 1,
		1.0f,  1.0f,  1.0f,  0, 1,
		1.0f,  1.0f,  1.0f,  0, 1,
		1.0f, -1.0f,  1.0f,  0, 0,
		-1.0f, -1.0f,  1.0f, 1, 0,

		// up
		-1.0f,  1.0f, -1.0f, 1, 0,
		1.0f,  1.0f, -1.0f,  1, 1,
		1.0f,  1.0f,  1.0f,  0, 1,
		1.0f,  1.0f,  1.0f,  0, 1,
		-1.0f,  1.0f,  1.0f, 0, 0,
		-1.0f,  1.0f, -1.0f, 1, 0,

		// down
		-1.0f, -1.0f, -1.0f, 0, 0,
		-1.0f, -1.0f,  1.0f, 0, 1,
		1.0f, -1.0f, -1.0f,  1, 0,
		1.0f, -1.0f, -1.0f,  1, 0,
		-1.0f, -1.0f,  1.0f, 0, 1,
		1.0f, -1.0f,  1.0f,  1, 1
	};


	// allocate a block of graphics memory (Vertex Buffer Object)
	unsigned int vertVBO;
	glGenBuffers(1, &vertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	int numBytes = sizeof(vertices);
	glBufferData(GL_ARRAY_BUFFER, numBytes, vertices, GL_STATIC_DRAW);  // set the size of the memory block, also upload some data
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	printOpenGLError();

	// make a structure (Vertex Array) that sets up the rendering state
	GLuint va = 0;
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glEnableVertexAttribArray(kInPosID);  // this is an identifier to the vertex shader variable 'inPosition'
	glVertexAttribPointer(kInPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);  // specify that the data for 'inPosition' comes from offset 0 in 'vbo' and that it is 4 tightly packed floats

	glEnableVertexAttribArray(kInUV);  // this is an identifier to the vertex shader variable 'inPosition'
	glVertexAttribPointer(kInUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float) * 3));  // specify that the data for 'inPosition' comes from offset 0 in 'vbo' and that it is 4 tightly packed floats
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Now we're ready to use the shader program
	gDC.fShader->UseProgram(Shader::EShaderKind::eShaderSkybox);
	glBindVertexArray(va);

	printOpenGLError();

	// set view / proj matrix.
	glm::mat4 projMat = glm::perspective(40.0f, 1.0f, 0.01f, 10.0f);
	glm::mat4 viewMat = gDC.fCamera->GetView(); //glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(-1, 1, 1), glm::vec3(0, 1, 0));
	glm::vec4 forwardVec = -glm::vec4(viewMat[0][2], viewMat[1][2], viewMat[2][2], viewMat[3][2]);
	viewMat = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(forwardVec), glm::vec3(0, 1, 0));

	gDC.fShader->UpdateUniformMat4("Proj", &projMat[0][0]);
	gDC.fShader->UpdateUniformMat4("View", &viewMat[0][0]);
	

	printOpenGLError();

	for (int i = 0; i < gDC.fBackground->GetNumTex(); i++) {
		int textureUnit = 0;
		glActiveTexture(GL_TEXTURE0 + textureUnit);  // this line and the one below associate kImage with GL_TEXTURE0
		printOpenGLError();
		glBindTexture(GL_TEXTURE_2D, gDC.fBackground->GetTex(i));
		printOpenGLError();
		// this sets the fragment shader variable 'kImage' to the value 0 - this means use the texture in GL_TEXTURE0
		gDC.fShader->UpdateUniform1i("kImage", textureUnit);
		printOpenGLError();

		glDrawArrays(GL_TRIANGLES, i * 6, 6);  // this draws a 'triangle strip' (search google images) that ends up drawing a textured rectangle
		printOpenGLError();
	}

	printOpenGLError();

	// Done.  Free resources.
	gDC.fShader->UseProgram(Shader::EShaderKind::eShaderNothing);
	glDeleteBuffers(1, &vertVBO);
	glDeleteVertexArrays(1, &va);

	printOpenGLError();
}



void renderScene(void) {
	printOpenGLError();

	ActivateMoveIfKeyPressed();

	// Init GL states.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_FALSE);
	glDisable(GL_BLEND);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderBackground();

	glDepthMask(GL_TRUE);

	gDC.fShader->UseProgram(Shader::EShaderKind::eShaderTexture);
	UpdateRenderMat(gDC);

	glBindTexture(GL_TEXTURE_2D, gDC.fTextureID);

	// should sort here.
	for (size_t i = 0; i < gDC.fMeshes.size(); i++) {
		glBindVertexArray(gDC.fVAO_ID[i + 1]);
		glDrawElements(GL_TRIANGLES, gDC.fMeshes[i].fIndices.size(), GL_UNSIGNED_SHORT, (void *)0);
		glBindVertexArray(0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	gDC.fShader->UseProgram(Shader::eShaderNothing); // glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
	//gDC.gShader->ShaderFileChangeWatcher();
}

void InitGL()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Volume Raycasting 3D");

	glutDisplayFunc(renderScene);
	//glutIdleFunc(renderScene);
	//glutReshapeFunc(changeSize);

	glm::vec3 eyepos(66.5f, 30.0f, 0.0f);
	gDC.SetCamera(eyepos, -3.141592 / 2, 0);
	gDC.AllocateInput();

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glewInit();

	//glDisable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_TEXTURE_3D);
	glEnable(GL_TEXTURE_2D);

	glClearColor(0.0, 0.0, 0.0, 1.0);


}

void LoadPlane()
{
	glBindVertexArray(gDC.fVAO_ID[0]);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gPlanes), gPlanes, GL_STATIC_DRAW);

	glGenBuffers(1, &gDC.fIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gDC.fIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gPlaneInds), gPlaneInds, GL_STATIC_DRAW);

	glGenBuffers(1, &gDC.fNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gDC.fNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gPlaneNormals), gPlaneNormals, GL_STATIC_DRAW);

	gDC.fVertexPos = glGetAttribLocation(gDC.fShader->GetProgram(), "inPositions");
	gDC.fNormalPos = glGetAttribLocation(gDC.fShader->GetProgram(), "inNormals");

	glEnableVertexAttribArray(gDC.fVertexPos);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(gDC.fVertexPos, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(gDC.fNormalPos);
	glBindBuffer(GL_ARRAY_BUFFER, gDC.fNormalBuffer);
	glVertexAttribPointer(gDC.fNormalPos, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindVertexArray(0);
}


void LoadSkybox()
{
	std::array<unsigned int, 6> skyboxIDs{0};
	skyboxIDs[0] = loadBMP_custom("./Skybox/ashcanyon_ft.bmp");
	skyboxIDs[1] = loadBMP_custom("./Skybox/ashcanyon_rt.bmp");
	skyboxIDs[2] = loadBMP_custom("./Skybox/ashcanyon_lf.bmp");
	skyboxIDs[3] = loadBMP_custom("./Skybox/ashcanyon_bk.bmp");
	skyboxIDs[4] = loadBMP_custom("./Skybox/ashcanyon_up.bmp");
	skyboxIDs[5] = loadBMP_custom("./Skybox/ashcanyon_dn.bmp");

	std::shared_ptr<IBackground> bg = std::make_shared<CubeBackground>();
	bg->SetCubeBackgroundTex(skyboxIDs);
	gDC.AddBackground(bg);
}


int main(int argc, char **argv) {
	try {

		glutInit(&argc, argv);
		InitGL();
		if (glewIsSupported("GL_VERSION_3_1"))
			printf("Ready for OpenGL 3.1.\n");
		else {
			printf("OpenGL 3.1 not supported\n");
			exit(1);
		}

		gDC.AddLight(glm::vec3(100.f, 100.f, 100.f), glm::vec3(1.0f, 1.0f, 1.0f));

#if MODELLOADING
		gDC.AllocateMeshAccess("truck_color.bmp", "./models/L200-OBJ/", "L200-OBJ.obj");
#else
		std::vector<glm::vec3> verts;
		LoadCube(verts);
#endif

		gDC.AllocateShader();
		printOpenGLError();

		if (gDC.fMeshes.size() > 99) { printf("too many meshes\n"); exit(-4); }

		glGenVertexArrays(gDC.fMeshes.size() + 1, gDC.fVAO_ID);

		gDC.fShader->UseProgram(Shader::EShaderKind::eShaderBasic);
		printOpenGLError();

		// Load Plane
		LoadPlane();

		// Load Skybox
		LoadSkybox();

		gDC.fShader->UseProgram(Shader::EShaderKind::eShaderTexture);
		printOpenGLError();

		for (size_t i = 0; i < gDC.fMeshes.size(); i++) {

			Mesh & mesh = gDC.fMeshes.at(i);
			Material & mat = mesh.fMat;

			// materials.

			glBindVertexArray(gDC.fVAO_ID[i + 1]);

			GLuint vertexBuffer;
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.fVertices.size() * sizeof(glm::vec3), &mesh.fVertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &gDC.fIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gDC.fIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.fIndices.size() * sizeof(unsigned short), &mesh.fIndices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &gDC.fNormalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, gDC.fNormalBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.fNormals.size() * sizeof(glm::vec3), &mesh.fNormals[0], GL_STATIC_DRAW);

			glGenBuffers(1, &gDC.fUVBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, gDC.fUVBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.fUVs.size() * sizeof(glm::vec2), &mesh.fUVs[0], GL_STATIC_DRAW);

			/*GLuint colorBuffer;
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, gColors.size() * sizeof(glm::vec3), &gColors[0], GL_STATIC_DRAW);
			*/

			gDC.fVertexPos = glGetAttribLocation(gDC.fShader->GetProgram(), "inPositions");
			gDC.fNormalPos = glGetAttribLocation(gDC.fShader->GetProgram(), "inNormals");
			gDC.fUVPos = glGetAttribLocation(gDC.fShader->GetProgram(), "inUV");
			//gColorPos = glGetAttribLocation(gDC.gShader->GetProgram(), "inColors");

			glEnableVertexAttribArray(gDC.fVertexPos);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(gDC.fVertexPos, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

			glEnableVertexAttribArray(gDC.fNormalPos);
			glBindBuffer(GL_ARRAY_BUFFER, gDC.fNormalBuffer);
			glVertexAttribPointer(gDC.fNormalPos, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

			glEnableVertexAttribArray(gDC.fUVPos);
			glBindBuffer(GL_ARRAY_BUFFER, gDC.fUVBuffer);
			glVertexAttribPointer(gDC.fUVPos, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//glEnableVertexAttribArray(gColorPos);
		//glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		//glVertexAttribPointer(gColorPos, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);


		printOpenGLError();


		UpdateRenderMat(gDC);

		glutMainLoop();

		EndGL();

	}
	catch (char * e) {
		std::cout << e << std::endl;
	}
	return 0;
}
