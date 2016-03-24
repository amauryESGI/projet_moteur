#include "Scene.h"

#include <iostream>

#include "glm\gtc\type_ptr.hpp"

#include "Time.h"

#include "WindowEvent.h"
#include "InputManager.h"

#include "Renderer.h"

Scene::Scene(GLFWwindow* window) : MainWindow(window)
{
	this->CameraList.push_back(&this->MainCamera);

	int widthWindow;
	int heightWindow;

	glfwGetWindowSize(this->MainWindow, &widthWindow, &heightWindow);
	glViewport(0, 0, widthWindow, heightWindow);
	this->MainCamera.setViewportAspectRatio((float)(widthWindow / heightWindow));

	this->Init();
}

void Scene::ResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	this->MainCamera.setViewportAspectRatio((float)(width / height));
}

void Scene::Init()
{
	this->lightManager.AddLight();

	//Initialisation du binder UBO
	this->BinderUBO.Light_UBO = this->lightManager.UBO;
	this->BinderUBO.ViewProj_UBO = this->MainCamera.UBO;

	WindowEvent::Initialize(this->MainWindow);

	WindowEvent::RegisterMouseButtonFunction(&InputManager::MouseButtonFunc);
	WindowEvent::RegisterMouseMotionFunction(&InputManager::MouseMotionFunc);
	WindowEvent::RegisterKeyFunction(&InputManager::KeyboardFunc);

	WindowEvent::RegisterWindowResizeFunction(std::bind(&Scene::ResizeWindow, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	this->MainCamera.Initialize();

	this->RenderUpdateFunction.push_back(&this->ld);
	this->LogicalUpdateFunction.push_back(&this->MainCamera);

	GameObject* obj = this->AddGameObject("alduin.obj");
	this->AddComponent(obj, new Renderer(&this->BinderUBO));
}

void Scene::Start()
{
	Time::Start();

	this->IsRunning = true;
	while (this->IsRunning)
	{
		Time::Update();

		//std::cout << Time::Fps << std::endl;

		glfwPollEvents();

		//this->CallStartFunction();

		this->UpdateLogic();
		this->UpdatePhysics();
		this->UpdateRender();

		//this->CallEndFunction();

		InputManager::EndFrame();

		if (glfwWindowShouldClose(this->MainWindow))
			this->IsRunning = false;

	}
	glfwTerminate();
	//AntTweakBar
	//TwTerminate();
}

void Scene::UpdateLogic()
{
	for (auto comp : this->LogicalUpdateFunction)
	{
		comp->Update();
	}
}

void Scene::UpdatePhysics()
{
	for (auto comp : this->PhysicalUpdateFunction)
	{
		comp->Update();
	}
}

//Attention pointer Chasing pas cool
void Scene::UpdateRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.F);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Projection = this->MainCamera.projection();
	glm::mat4 View = this->MainCamera.view();
	glm::mat4 World = glm::mat4(1.0f);

	render.ProjectionMatrix = Projection;
	render.ViewMatrix = View;
	render.WorldMatrix = World;

	this->lightManager.getNumberLight();

	glBindBuffer(GL_UNIFORM_BUFFER, MainCamera.UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4) * 3, glm::value_ptr(MainCamera.CameraViewProj.viewMatrix));

	glBindBuffer(GL_UNIFORM_BUFFER, this->lightManager.UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light) * this->lightManager.getNumberLight(), this->lightManager.getLightList());

	for (auto updateFunc : this->RenderUpdateFunction)
	{
		updateFunc->Draw(render);
	}

	//En dernier pour limiter l'overdraw
	this->Skybox.Draw(render);

	glfwSwapBuffers(this->MainWindow);
}

void Scene::AddComponent(GameObject* object, Component* comp)
{
	object->AddComponent(comp);
	switch (comp->getType())
	{
	case ComponentType::GraphicalComponent:
		this->RenderUpdateFunction.push_back((GraphicsComponent*)comp);
		break;
	}
}

Scene::~Scene()
{
}
