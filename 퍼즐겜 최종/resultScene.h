#pragma once
#include "gameNode.h"

enum class RESULTSTATE
{
	RESULTBOXDOWN,
	RESULTSELECT
};

class resultScene : public gameNode
{
private:
	RESULTSTATE _state;
	RECT _quit;
	RECT _regam;

	int _hi;
	int _sco;

	int _y;

public:
	resultScene() {}
	~resultScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

};

