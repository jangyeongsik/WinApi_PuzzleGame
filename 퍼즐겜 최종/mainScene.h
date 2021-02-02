#pragma once
#include "gameNode.h"

class mainScene : public gameNode
{
private:
	int _offsetX;
	int _offsetY;

	RECT _start;
	RECT _exit;

public:
	mainScene() {}
	~mainScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

};

