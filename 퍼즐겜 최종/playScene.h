#pragma once
#include "gameNode.h"
#include "block.h"
#include "blockManager.h"

enum BLOCKTAILSTATE
{
	BLOCKTAIL_FULL,
	BLOCKTAIL_EMPTY,
	BLOCKTAIL_POP
};

struct tagBlockInfo
{
	BLOCKTAILSTATE state;
	block* block;
	RECT rc;
	float x, y;
	float frameTime;
	int frameX;
};

class playScene : public gameNode
{
private:
	vector<int> _vCheckWid;
	vector<int> _vCheckHei;

	tagBlockInfo _block[10][10];
	blockManager* _bm;

	int _currentScore;
	int _highScore;

	int _count1;
	int _count2;
	int _count3;

public:
	playScene() {}
	~playScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setBlocks();
	void CheckCount();
	bool CheckWid(int arr);
	bool CheckHei(int arr);

	bool CheckArea(int i, int j, POINT pt);
	bool VCeckArea(int i, int j, vector<POINT> pt);

};

