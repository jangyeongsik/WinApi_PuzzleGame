#include "stdafx.h"
#include "block_2048.h"

HRESULT block_2048::init(int i, int j)
{

	_x = 151 + (j * 90);
	_y = 151 + (i * 90);
	_rc = RectMakeCenter(_x, _y, 80, 80);
	_location = { j,i };
	_state = BLOCKMOVESTATE::BLOCK_IDLE;

	_offsetX = 0;
	_offsetY = 0;
	_isCombine = false;

	switch (GetRandom(10))
	{
	case 1:
		_value = 4;
		break;
	default:
		_value = 2;
		break;
	}

	return S_OK;
}

void block_2048::release()
{
}

void block_2048::update()
{
	switch (_state)
	{
	case BLOCKMOVESTATE::BLOCK_MOVE_LEFT:
		_x -= 20;
		if (_x < 151 + (_location.x * 90))
		{
			_x = 151 + (_location.x * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_RIGHT:
		_x += 20;

		if (_x > 151 + (_location.x * 90))
		{
			_x = 151 + (_location.x * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_UP:
		_y -= 20;
		if (_y < 151 + (_location.y * 90))
		{
			_y = 151 + (_location.y * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_DOWN:
		_y += 20;
		if (_y > 151 + (_location.y * 90))
		{
			_y = 151 + (_location.y * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_IDLE:
		break;
	
	}


	_rc = RectMakeCenter(_x, _y, 80, 80);
}

void block_2048::render()
{
	string str = to_string(_value);
	IMAGEMANAGER->findImage(str)->renderCenter(getMemDC(),_x,_y);
	//Rectangle(getMemDC(), _rc);
	/*char temp[129];
	wsprintf(temp, "%d", _offsetX);
	TextOut(getMemDC(), _x, _y-20, temp, strlen(temp));
	wsprintf(temp, "%d", _offsetY);
	TextOut(getMemDC(), _x, _y, temp, strlen(temp));
	wsprintf(temp, "%d", _location.x);
	TextOut(getMemDC(), _x, _y+20, temp, strlen(temp));
	wsprintf(temp, "%d", _location.y);
	TextOut(getMemDC(), _x, _y+40, temp, strlen(temp));*/
}

void block_2048::setLocation(int i, int j)
{
	if (_location.x < j)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_RIGHT;
	}
	else if (_location.x > j)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_LEFT;
	}
	else if (_location.y < i)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_DOWN;
	}
	else if (_location.y > i)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_UP;
	}

	_location = { j,i };

}
