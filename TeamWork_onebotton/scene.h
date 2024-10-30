#pragma once

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void onEnter(){}//シーンが切り替わったときに呼ばれる
	virtual void onInput(char* keys,char* prekeys) {
		(void)keys;
		(void)prekeys;
	}
	virtual void update(){}
	virtual void draw(){}
	virtual void onExit(){}//シーンが切り替わるときに呼ばれる

};
