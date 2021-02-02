#pragma once
#include "gameNode.h"

enum BLOCKCOLOR
{
	BLOCK_BLUE,
	BLOCK_RED,
	BLOCK_YELLOW,
	BLOCK_PURPLE,
	BLOCK_GREEN,
	BLOCK_PINK
};

class block : public gameNode
{
private:
	vector<POINT> _vPoint;
protected:
	BLOCKCOLOR _color;
	float _startX, _startY;
	float _x, _y;
	float _distX, _distY;
	RECT _blockRC;
	image* _blockIg;

	bool _isPop;

	float _frameTime;
	int _frameX;

public:
	block() {}
	~block() {}

	HRESULT init(float x, float y, BLOCKCOLOR color);
	void release();
	void update();
	void render();

	void moveBlockPos(float x, float y);
	void resetBlockPos();

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setDistX(float x) { _distX = x; }
	void setDistY(float y) { _distY = y; }
	RECT getBlockRC() { return _blockRC; }
	image* getBlockIG() { return _blockIg; }
	void pushPoint(POINT xy) { _vPoint.push_back(xy); }
	void popPoint() { _vPoint.pop_back(); }
	vector<POINT> getVPoint() { return _vPoint; }

	bool getIsPop() { return _isPop; }
	void setIsPop(bool pop) { _isPop = pop; }
	int getFrameX() { return _frameX; }
	BLOCKCOLOR getColor() { return _color; }
};

