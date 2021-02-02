#include "stdafx.h"
#include "2048Scene.h"

HRESULT PLAYSCENE::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	temp = RectMakeCenter(_x, _y, 80, 80);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_base[i][j].rc = RectMakeCenter(151 + (j * 90), 151 + (i * 90), 80, 80);
			_base[i][j].state = BASE_EMPTY;
			_base[i][j].value = 0;
		}
	}

	_state = PLAYSCENESTATE::BLOCK_IDLE;
	_isCombine = false;
	_push = false;

	_currentScore = 0;
	_hightScore = scoreData::getSingleton()->loadData("2048.txt");

	
	pushBlock();

	return S_OK;
}

void PLAYSCENE::release()
{

}

void PLAYSCENE::update()
{
	//cout << (int)_state << endl;
	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->update();
	}

	if (_currentScore > _hightScore) _hightScore = _currentScore;

	switch (_state)
	{
	case PLAYSCENESTATE::BLOCK_SET_LEFT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			
			POINT temp = _vBlock[i]->getLocation();
			for (int j = 0; j < _vBlock[i]->getLocation().x; j++)
			{
				if (_base[temp.y][j].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetX(count);
			count = 0;
		}
		
		_state = PLAYSCENESTATE::BLOCK_MOVE_LEFT;
		if (CheckOffsetX()) _push = true;
		else _push = false;
	
		break;
	case PLAYSCENESTATE::BLOCK_SET_RIGHT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			for (int j = temp.x + 1; j < 4; j++)
			{
				if (_base[temp.y][j].state == BASE_FULL)
				{
					count++;
				}
			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetX(3 - count);
			count = 0;
		}
		

		_state = PLAYSCENESTATE::BLOCK_MOVE_RIGHT;
		if (CheckOffsetX()) _push = true;
		else _push = false;
		
		break;
	case PLAYSCENESTATE::BLOCK_SET_UP:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			for (int j = 0; j < _vBlock[i]->getLocation().y; j++)
			{
				if (_base[j][temp.x].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetY(count);
			count = 0;
		}
		
		_state = PLAYSCENESTATE::BLOCK_MOVE_UP;
		if (CheckOffsetY()) _push = true;
		else _push = false;
		
		break;
	case PLAYSCENESTATE::BLOCK_SET_DOWN:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();

			for (int j = temp.y + 1; j < 4; j++)
			{
				if (_base[j][temp.x].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetY(3 - count);
			count = 0;
		}
		

		_state = PLAYSCENESTATE::BLOCK_MOVE_DOWN;
		if (CheckOffsetY()) _push = true;
		else _push = false;
		
		
		break;
	case PLAYSCENESTATE::BLOCK_MOVE_LEFT:
		
		for (int i = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(temp.y, _vBlock[i]->getOffsetX());
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}
		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size();j++)
			{
				if (i == j) continue;
				RECT temp;
				if (IntersectRect(&temp, &_vBlock[i]->getRect(), &_vBlock[j]->getRect()))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue();
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}
		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_LEFT;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}
		
		
		break;
	case PLAYSCENESTATE::BLOCK_MOVE_RIGHT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(temp.y, _vBlock[i]->getOffsetX());
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				if (IntersectRect(&temp, &_vBlock[i]->getRect(), &_vBlock[j]->getRect()))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue();
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}

		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_RIGHT;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}
		
		break;
	case PLAYSCENESTATE::BLOCK_MOVE_UP:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(_vBlock[i]->getOffsetY(), temp.x);
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				if (IntersectRect(&temp, &_vBlock[i]->getRect(), &_vBlock[j]->getRect()))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue();
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}

		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_UP;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}

		
		break;
	case PLAYSCENESTATE::BLOCK_MOVE_DOWN:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(_vBlock[i]->getOffsetY(), temp.x);
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				if (IntersectRect(&temp, &_vBlock[i]->getRect(), &_vBlock[j]->getRect()))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue();
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}

		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_DOWN;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}

		
		break;
	case PLAYSCENESTATE::BLOCK_COMBINE_LEFT:

		_count = 0;

		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().x == i)
				{
					if (_base[_vBlock[j]->getLocation().y][i-1].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetX(i - 1);
						_vBlock[j]->setIsCombine(true);
						_base[_vBlock[j]->getLocation().y][i].state = BASE_EMPTY;
						_base[_vBlock[j]->getLocation().y][i].value = 0;
						_count++;
					}
				}
			}
		}

		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_LEFT;
			_isCombine = true;
		}
		break;
	case PLAYSCENESTATE::BLOCK_COMBINE_RIGHT:
		_count = 0;
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().x == i)
				{
					if (_base[_vBlock[j]->getLocation().y][i + 1].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetX(i + 1);
						_vBlock[j]->setIsCombine(true);
						_base[_vBlock[j]->getLocation().y][i].state = BASE_EMPTY;
						_base[_vBlock[j]->getLocation().y][i].value = 0;
						_count++;
					}
				}
			}
		}

		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_RIGHT;
			_isCombine = true;
		}
		
		break;
	case PLAYSCENESTATE::BLOCK_COMBINE_UP:
		_count = 0;
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().y == i)
				{
					if (_base[i - 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetY(i - 1);
						_vBlock[j]->setIsCombine(true);
						_base[i][_vBlock[j]->getLocation().x].state = BASE_EMPTY;
						_base[i][_vBlock[j]->getLocation().x].value = 0;
						_count++;
					}
				}
			}
		}

		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_UP;
			_isCombine = true;
		}
		
		break;
	case PLAYSCENESTATE::BLOCK_COMBINE_DOWN:
		_count = 0;
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().y == i)
				{
					if (_base[i + 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetY(i + 1);
						_vBlock[j]->setIsCombine(true);
						_base[i][_vBlock[j]->getLocation().x].state = BASE_EMPTY;
						_base[i][_vBlock[j]->getLocation().x].value = 0;
						_count++;
					}
				}
			}
		}

		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_DOWN;
			_isCombine = true;
		}
		
		break;
	case PLAYSCENESTATE::BLOCK_IDLE:
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_LEFT;
		}
	
		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_RIGHT;
			
		}
		if (INPUT->GetKeyDown(VK_UP))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_UP;
			
		}
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_DOWN;
			
		}
		if (CheckBase() == false && CheckCombine() == false)
		{
			scoreData::getSingleton()->saveData("2048.txt", _hightScore);
			scoreData::getSingleton()->saveCurrentScore(_currentScore);
			SCENEMANAGER->loadScene("2048result");
		}
		

		break;
	}
	
	
	

}

void PLAYSCENE::render()
{
	IMAGEMANAGER->findImage("base")->render(getMemDC(), 100, 100);

	char temp[128];

	HFONT font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Hobo Bt");
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(temp, "score : %d", _currentScore);
	TextOut(getMemDC(), WINSIZEX / 2 + 135, 150, temp, strlen(temp));
	wsprintf(temp, "highScore : %d", _hightScore);
	TextOut(getMemDC(), WINSIZEX / 2 + 70, 200, temp, strlen(temp));
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);


	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->render();
	}


	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char str[128];
			wsprintf(str, "%d", _base[i][j].value);
			TextOut(getMemDC(), _base[i][j].rc.left, _base[i][j].rc.top, str, strlen(str));
		}
	}*/
	char str[128];
	
	
}

void PLAYSCENE::pushBlock()
{
	int i = GetRandom(4);
	int j = GetRandom(4);
	if (_base[i][j].state == BASE_FULL)
	{
		while (true)
		{
			i = GetRandom(4);
			j = GetRandom(4);
			if (_base[i][j].state == BASE_EMPTY) break;
		}
	}
	block_2048* bl = new block_2048;
	bl->init(i, j);
	_vBlock.push_back(bl);
	_base[i][j].state = BASE_FULL;
	_base[i][j].value = bl->getValue();
}

void PLAYSCENE::popBlock(int arr)
{
}

bool PLAYSCENE::CheckState()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if ((int)_vBlock[i]->getState() != 4)
		{
			return false;
		}
	}
	return true;
}

bool PLAYSCENE::CheckOffsetX()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i]->getOffsetX() != _vBlock[i]->getLocation().x)
		{
			return true;
		}
	}
	return false;
}

bool PLAYSCENE::CheckOffsetY()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i]->getOffsetY() != _vBlock[i]->getLocation().y)
		{
			return true;
		}
	}
	return false;
}

bool PLAYSCENE::CheckCombine()
{
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().x == i)
			{
				if (_base[_vBlock[j]->getLocation().y][i - 1].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().x == i)
			{
				if (_base[_vBlock[j]->getLocation().y][i + 1].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().y == i)
			{
				if (_base[i - 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().y == i)
			{
				if (_base[i + 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool PLAYSCENE::CheckBase()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_base[i][j].state == BASE_EMPTY) return true;
		}
	}
	return false;
}




