#pragma once
#include "gameNode.h"

enum class RESULT2048STATE
{
	RESULTBOXDOWN,
	RESULTSELECT
};

class result_2048 : public gameNode
{
private:
	RESULT2048STATE _state;
	RECT _quit;
	RECT _regam;

	int _hi;
	int _sco;

	int _y;

public:
	result_2048() {}
	~result_2048() {}

	HRESULT init();
	void release();
	void update();
	void render();

};


