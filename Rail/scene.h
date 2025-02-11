#pragma once
#include "Camera.h"
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void onEnter(){}//シーンに入るときに呼び出される
	virtual void onInput(char* keys,char* prekeys) {
		(void)keys;
		(void)prekeys;
	}
	virtual void update(){}
	virtual void draw(const Camera& camera){
		(void)camera;
	}
	virtual void onExit(){}//シーンが切り替わるときに呼ばれる


private:

};
