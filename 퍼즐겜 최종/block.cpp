#include "stdafx.h"
#include "block.h"

HRESULT block::init(float x, float y, BLOCKCOLOR color)
{
	_startX = x;
	_startY = y;
	_x = x;
	_y = y;
	_distX = 0;
	_distY = 0;
	_blockRC = RectMakeCenter(_x, _y, 36, 36);
	_vPoint.push_back(PointMake(0, 0));
	_isPop = false;

	switch (color)
	{
	case BLOCK_BLUE:
		_blockIg =  IMAGEMANAGER->findImage("block_blue");
		_color = BLOCK_BLUE;
		break;
	case BLOCK_RED:
		_blockIg = IMAGEMANAGER->findImage("block_red");
		_color = BLOCK_RED;
		break;
	case BLOCK_YELLOW:
		_blockIg = IMAGEMANAGER->findImage("block_yellow");
		_color = BLOCK_YELLOW;
		break;
	case BLOCK_PURPLE:
		_blockIg = IMAGEMANAGER->findImage("block_purple");
		_color = BLOCK_PURPLE;
		break;
	case BLOCK_GREEN:
		_blockIg = IMAGEMANAGER->findImage("block_green");
		_color = BLOCK_GREEN;
		break;
	case BLOCK_PINK:
		_blockIg = IMAGEMANAGER->findImage("block_pink");
		_color = BLOCK_PINK;
		break;
	}

	return S_OK;
}

void block::release()
{
}

void block::update()
{
	if (_isPop)
	{
		switch (_color)
		{
		case BLOCK_BLUE:
			_blockIg = IMAGEMANAGER->findImage("blue_pop");
			break;
		case BLOCK_RED:
			_blockIg = IMAGEMANAGER->findImage("red_pop");
			break;
		case BLOCK_YELLOW:
			_blockIg = IMAGEMANAGER->findImage("yellow_pop");
			break;
		case BLOCK_PURPLE:
			_blockIg = IMAGEMANAGER->findImage("purple_pop");
			break;
		case BLOCK_GREEN:
			_blockIg = IMAGEMANAGER->findImage("green_pop");
			break;
		case BLOCK_PINK:
			_blockIg = IMAGEMANAGER->findImage("pink_pop");
			break;
		}
	}

}

void block::render()
{
	_blockIg->renderCenter(getMemDC(),_x,_y);
}

void block::moveBlockPos(float x, float y)
{
	_x = x - _distX;
	_y = y - _distY;
	_blockRC = RectMakeCenter(_x, _y, 30, 30);
}

void block::resetBlockPos()
{
	_x = _startX;
	_y = _startY;
	_blockRC = RectMakeCenter(_x, _y, 30, 30);
}
