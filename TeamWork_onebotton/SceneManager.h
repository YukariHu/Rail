#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <Scene.h>
#include <TitleScene.h>
#include <ClearScene.h>
#include <stageScene.h>
#include <vector>
class SceneManager
{

public:
	enum class SceneType
	{
		Title,
		StageSelect,
		Game,
	};
	SceneManager() = default;
	~SceneManager() = default;
	
	void init();
	void onInput(char* keys, char* prekeys);
	void update();
	
	void draw(const Camera& camera);

	void setCurrentScene(Scene* scene);


	void switchScene(SceneType type);
	

private:

	Scene* currentScene = nullptr;
	Scene* tieleScene = nullptr;
	Scene* stageSelectScene = nullptr;

	std::vector<Scene*> stageScene;

	//Scene* gameSceneA = nullptr;
	//Scene* gameSceneB = nullptr;
public:
	int stageNum = 2;//ステージの総数
	int selectedStage = 0;//選択されているステージ
	//Scene m_scene;


};

#endif // !SCENEMANAGER_H