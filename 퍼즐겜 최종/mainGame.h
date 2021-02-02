#pragma once
#include "gameNode.h"
#include "animation.h"
#include "block.h"
#include "mainScene.h"
#include "playScene.h"
#include "resultScene.h"
#include "2048Scene.h"
#include "result_2048.h"

struct tagTailInfo
{
	block* block;
	bool isEmpty;
	int space;

};

class mainGame : public gameNode
{
private:


public:
	mainGame() {}
	~mainGame() {}

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void imageInit();
	
};

