#include "SceneManager.h"
#include "Camera.h"

void SceneManager::init()
{
	tieleScene = new TitleScene();
	clearSCene = new ClearScene();
	stageScene.push_back(new StageScene(0));
	setCurrentScene(tieleScene);
	//setCurrentScene(stageScene[1]);
}

void SceneManager::onInput(char* keys, char* prekeys)
{
	currentScene->onInput(keys, prekeys);

}

void SceneManager::update()
{
	currentScene->update();
}

void SceneManager::draw(const Camera& camera)
{
	currentScene->draw(camera);
}

void SceneManager::setCurrentScene(Scene* scene)
{
	currentScene = scene;
	currentScene->onEnter();
}

void SceneManager::switchScene(SceneType type)
{
	currentScene->onExit();
	switch (type)
	{
	case SceneManager::SceneType::Title:
		currentScene = tieleScene;
		break;
	case SceneManager::SceneType::Claer:
		currentScene = clearSCene;
		break;
	case SceneManager::SceneType::Game:
		currentScene = stageScene[selectedStage];
		break;
	default:
		break;
	}
	currentScene->onEnter();
}
