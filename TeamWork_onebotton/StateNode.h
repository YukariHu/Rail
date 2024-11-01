#pragma once
class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;


	virtual void onEnter() {};
	virtual void onUpdate() {};
	virtual void onExit() {};
		
private:

};
