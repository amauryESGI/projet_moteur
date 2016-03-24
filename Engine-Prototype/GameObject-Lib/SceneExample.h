#pragma once

#include <vector>
#include <memory>

#define GLEW_STATIC
#include "GL\glew.h"

#define GLFW_INCLUDE_GLU
#include "GLFW\glfw3.h"

#include "Camera.h"
#include "Helper.h"
#include "Skybox.h"
#include "Landmark.h"
#include "GameObject.h"
#include "UBO_Binder.h"

#include "LightManager.h"

#include "GraphicsComponent.h"
#include "LogicalComponent.h"
#include "PhysicsComponent.h"

class Scene
{
public:
	Scene(GLFWwindow* window);

	void Scene::Init();
	void Scene::Start();
	~Scene();
private:
	bool IsRunning;

	GLFWwindow* MainWindow;
	Camera MainCamera;

	Landmark ld;
	Skybox Skybox;
	UBO_Binder BinderUBO;

	LightManager lightManager;
	RenderDataBinder render;

	std::vector<Camera*> CameraList;
	std::vector<std::unique_ptr<GameObject>> ObjectList;


	std::vector<LogicalComponent*> LogicalUpdateFunction;
	std::vector<PhysicsComponent*> PhysicalUpdateFunction;
	std::vector<GraphicsComponent*> RenderUpdateFunction;


	void Scene::UpdateLogic();
	void Scene::UpdatePhysics();
	void Scene::UpdateRender();
	void ResizeWindow(GLFWwindow* window, int width, int height);

	GameObject* Scene::AddGameObject( Mesh m)
	{
		GameObject* obj = new GameObject(m);
		this->ObjectList.push_back(std::unique_ptr<GameObject>(obj));
		return obj;
	}

	GameObject* Scene::AddGameObject(std::string inputFile)
	{
		GameObject* obj = new GameObject(inputFile);
		this->ObjectList.push_back(std::unique_ptr<GameObject>(obj));
		return obj;
	}

	void Scene::AddComponent(GameObject* object, Component* comp);
};

