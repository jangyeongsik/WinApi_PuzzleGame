#pragma once
#include "gameNode.h"
#include "block_2048.h"

enum class PLAYSCENESTATE
{
	BLOCK_SET_LEFT,
	BLOCK_SET_RIGHT,
	BLOCK_SET_UP,
	BLOCK_SET_DOWN,
	BLOCK_MOVE_LEFT,
	BLOCK_MOVE_RIGHT,
	BLOCK_MOVE_UP,
	BLOCK_MOVE_DOWN,
	BLOCK_COMBINE_LEFT,
	BLOCK_COMBINE_RIGHT,
	BLOCK_COMBINE_UP,
	BLOCK_COMBINE_DOWN,
	BLOCK_IDLE
};

enum BASESTATE
{
	BASE_EMPTY,
	BASE_FULL
};

struct tagBaseInfo
{
	RECT rc;
	BASESTATE state;
	int value;
};

class PLAYSCENE : public gameNode
{
private:
	PLAYSCENESTATE _state;
	bool _isCombine;

	tagBaseInfo _base[4][4];


	vector<block_2048*> _vBlock;

	vector<pair<POINT, POINT>> _vOffset;

	int _currentScore;
	int _hightScore;

	RECT temp;
	int _x, _y;
	int _count;
	bool _push;
public:
	PLAYSCENE() {}
	~PLAYSCENE() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void pushBlock();
	void popBlock(int arr);

	bool CheckState();
	bool CheckOffsetX();
	bool CheckOffsetY();
	bool CheckCombine();
	bool CheckBase();
};

