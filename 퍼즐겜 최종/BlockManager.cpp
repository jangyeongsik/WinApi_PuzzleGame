#include "stdafx.h"
#include "blockManager.h"

void blockManager::update(BMSTATE bs)
{
	
	switch (bs)
	{
	case BLOCKMANAGER_IDLE:
		/*for (int i = 0; i < _vBlock.size(); i++)
		{
			if (PtInRect(&_vBlock[i].second->getBlockRC(), _ptMouse)) break;
			if (i == _vBlock.size() - 1)
			{
				_bmState = BLOCKMANAGER_NONUPDATE;
			}
		}*/
		//if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < _vBlock.size(); i++)
			{
				if (PtInRect(&_vBlock[i].second->getBlockRC(), _ptMouse))
				{
					_currentMoveGroup = _vBlock[i].first;
					_currentMoveIndex = i;
					for (int i = 0; i < _vBlock.size(); i++)
					{
						if (_vBlock[i].first == _currentMoveGroup)
						{
							_vBlock[i].second->setDistX(_ptMouse.x - _vBlock[i].second->getX());
							_vBlock[i].second->setDistY(_ptMouse.y - _vBlock[i].second->getY());
						}
					}
					_bmState = BLOCKMANAGER_MOVEBLOCK;
				}
			}
		}

		break;
	case BLOCKMANAGER_MOVEBLOCK:
		for (int i = 0; i < _vBlock.size(); i++)
		{
			if (_vBlock[i].first == _currentMoveGroup)
			{
				_vBlock[i].second->moveBlockPos(_ptMouse.x, _ptMouse.y);
			}
		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			_bmState = BLOCKMANAGER_NONUPDATE;
		}
		break;
	case BLOCKMANAGER_NONUPDATE:
		for (int i = 0; i < _vBlock.size(); i++)
		{
			if (PtInRect(&_vBlock[i].second->getBlockRC(), _ptMouse))
			{
				_bmState = BLOCKMANAGER_IDLE;
			}
		}
		break;
	}
	//if (INPUT->GetKeyDown(VK_LBUTTON))
	//{
	//	for (int i = 0; i < _vBlock.size(); i++)
	//	{
	//		if (PtInRect(&_vBlock[i].second->getBlockRC(), _ptMouse))
	//		{
	//			_currentMoveGroup = _vBlock[i].first;
	//			for (int i = 0; i < _vBlock.size(); i++)
	//			{
	//				if (_vBlock[i].first == _currentMoveGroup)
	//				{
	//					_vBlock[i].second->setDistX(_ptMouse.x - _vBlock[i].second->getX());
	//					_vBlock[i].second->setDistY(_ptMouse.y - _vBlock[i].second->getY());
	//				}
	//			}
	//		}
	//	}
	//}
	//if (INPUT->GetKey(VK_LBUTTON))
	//{
	//	for (int i = 0; i < _vBlock.size(); i++)
	//	{
	//		if (_vBlock[i].first == _currentMoveGroup)
	//		{
	//			_vBlock[i].second->moveBlockPos(_ptMouse.x, _ptMouse.y);
	//		}
	//	}
	//}
}

void blockManager::render()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i].second->render();
	}
}

void blockManager::popGroup(int group)
{
	for (int i = 0; i < _vBlock.size();)
	{
		if (_vBlock[i].first == group)
		{
			_vBlock.erase(_vBlock.begin() + i);
		}
		else i++;
	}
}

void blockManager::resetBlockPos(int group)
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i].first == group)
		{
			_vBlock[i].second->resetBlockPos();
		}
	}
}

void blockManager::setOMino(int group, float x, float y, int size)
{
	if (size == 2)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				block* _bl = new block;
				_bl->init(x - 18, y - 18, BLOCK_GREEN);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(1, 1));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x - 18, y + 18, BLOCK_GREEN);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(1, -1));
				_vBlock.push_back(make_pair(group, _bl));
			}
			else
			{
				block* _bl = new block;
				_bl->init(x + 18, y - 18, BLOCK_GREEN);
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(-1, 1));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x + 18, y + 18, BLOCK_GREEN);
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(-1, -1));
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				block* _bl = new block;
				_bl->init(x - 36, y - 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(2, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(1, 1));
				_bl->pushPoint(PointMake(2, 1));
				_bl->pushPoint(PointMake(0, 2));
				_bl->pushPoint(PointMake(1, 2));
				_bl->pushPoint(PointMake(2, 2));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x-36, y, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(2, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(1, -1));
				_bl->pushPoint(PointMake(2, -1));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(1, 1));
				_bl->pushPoint(PointMake(2, 1));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x - 36, y + 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(2, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(1, -1));
				_bl->pushPoint(PointMake(2, -1));
				_bl->pushPoint(PointMake(0, -2));
				_bl->pushPoint(PointMake(1, -2));
				_bl->pushPoint(PointMake(2, -2));
				_vBlock.push_back(make_pair(group, _bl));
			}
			else if(i == 1)
			{
				block* _bl = new block;
				_bl->init(x, y - 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(1, 1));
				_bl->pushPoint(PointMake(-1, 1));
				_bl->pushPoint(PointMake(0, 2));
				_bl->pushPoint(PointMake(1, 2));
				_bl->pushPoint(PointMake(-1, 2));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x, y, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(1, 1));
				_bl->pushPoint(PointMake(-1, 1));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(1, -1));
				_bl->pushPoint(PointMake(-1, -1));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x, y + 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(1, 0));
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(1, -1));
				_bl->pushPoint(PointMake(-1, -1));
				_bl->pushPoint(PointMake(0, -2));
				_bl->pushPoint(PointMake(1, -2));
				_bl->pushPoint(PointMake(-1, -2));
				_vBlock.push_back(make_pair(group, _bl));
			}
			else
			{
				block* _bl = new block;
				_bl->init(x + 36, y - 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(-2, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(-1, 1));
				_bl->pushPoint(PointMake(-2, 1));
				_bl->pushPoint(PointMake(0, 2));
				_bl->pushPoint(PointMake(-1, 2));
				_bl->pushPoint(PointMake(-2, 2));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x+36, y, BLOCK_BLUE);
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(-2, 0));
				_bl->pushPoint(PointMake(0, 1));
				_bl->pushPoint(PointMake(-1, 1));
				_bl->pushPoint(PointMake(-2, 1));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(-1, -1));
				_bl->pushPoint(PointMake(-2, -1));
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(x + 36, y + 36, BLOCK_BLUE);
				_bl->pushPoint(PointMake(-1, 0));
				_bl->pushPoint(PointMake(-2, 0));
				_bl->pushPoint(PointMake(0, -1));
				_bl->pushPoint(PointMake(-1, -1));
				_bl->pushPoint(PointMake(-2, -1));
				_bl->pushPoint(PointMake(0, -2));
				_bl->pushPoint(PointMake(-1, -2));
				_bl->pushPoint(PointMake(-2, -2));
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
	}
}

void blockManager::setIMino(int group, float x, float y, int size, bool location)
{
	block* _bl;
	int startX = 0;
	int startY = 0;
	switch (size)
	{
	case 1:
		_bl = new block;
		_bl->init(x, y, BLOCK_PURPLE);
		_vBlock.push_back(make_pair(group, _bl));
		break;
	case 2:
		startX = x - 18;
		startY = y - 18;
		if (location == true)
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), y, BLOCK_YELLOW);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(x, startY + (i * 36), BLOCK_YELLOW);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, 1));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		break;
	case 3:
		startX = x - 36;
		startY = y - 36;
		if (location == true)
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), y, BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 2:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(x, startY + (i * 36), BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0 , 1));
					_bl->pushPoint(PointMake(0 , 2));
					break;
				case 1:
					_bl->pushPoint(PointMake(0 , -1));
					_bl->pushPoint(PointMake(0 , 1));
					break;
				case 2:
					_bl->pushPoint(PointMake(0 , -1));
					_bl->pushPoint(PointMake(0 , -2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		break;
	case 4:
		startX = x - 54;
		startY = y - 54;
		if (location == true)
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), y, BLOCK_PINK);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(3, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				case 2:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 3:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(-3, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(x, startY + (i * 36), BLOCK_PINK);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					_bl->pushPoint(PointMake(0, 3));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(0, 1));
					break;
				case 3:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(0, -3));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		break;
	case 5:
		startX = x - 72;
		startY = y - 72;
		if (location == true)
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), y, BLOCK_RED);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(3, 0));
					_bl->pushPoint(PointMake(4, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(3, 0));
					break;
				case 2:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				case 3:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(-3, 0));
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 4:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(-3, 0));
					_bl->pushPoint(PointMake(-4, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(x, startY + (i * 36), BLOCK_RED);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					_bl->pushPoint(PointMake(0, 3));
					_bl->pushPoint(PointMake(0, 4));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					_bl->pushPoint(PointMake(0, 3));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 3:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(0, -3));
					_bl->pushPoint(PointMake(0, 1));
					break;
				case 4:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(0, -3));
					_bl->pushPoint(PointMake(0, -4));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
		}
		break;
	}
}

// 1: LT	2: RT	3: LB	4: RB
void blockManager::setLMino(int group, float x, float y, int size, int angle)
{
	block* _bl;
	int startX = 0;
	int startY = 0;

	switch (size)
	{
	case 2:
		switch (angle)
		{
		case 1:
			_bl = new block;
			_bl->init(x - 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(1, 0));
			_bl->pushPoint(PointMake(0, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x + 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(-1, 0));
			_bl->pushPoint(PointMake(-1, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x - 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(0, -1));
			_bl->pushPoint(PointMake(1, -1));
			_vBlock.push_back(make_pair(group, _bl));
			break;
		case 2:
			_bl = new block;
			_bl->init(x - 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(1, 0));
			_bl->pushPoint(PointMake(1, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x + 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(-1, 0));
			_bl->pushPoint(PointMake(0, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x + 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(-1, -1));
			_bl->pushPoint(PointMake(0, -1));
			_vBlock.push_back(make_pair(group, _bl));
			break;
		case 3:
			_bl = new block;
			_bl->init(x - 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(0, 1));
			_bl->pushPoint(PointMake(1, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x + 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(-1, 0));
			_bl->pushPoint(PointMake(-1, -1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x - 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(1, 0));
			_bl->pushPoint(PointMake(0, -1));
			_vBlock.push_back(make_pair(group, _bl));
			break;
		case 4:
			_bl = new block;
			_bl->init(x + 18, y - 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(0, 1));
			_bl->pushPoint(PointMake(-1, 1));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x + 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(0, -1));
			_bl->pushPoint(PointMake(-1, 0));
			_vBlock.push_back(make_pair(group, _bl));
			_bl = new block;
			_bl->init(x - 18, y + 18, BLOCK_YELLOW);
			_bl->pushPoint(PointMake(1, 0));
			_bl->pushPoint(PointMake(1, -1));
			_vBlock.push_back(make_pair(group, _bl));
			break;
		}
		break;
	case 3:
		switch (angle)
		{
		case 1:
			startX = x - 36;
			startY = y - 36;
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), startY, BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 1:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-1, 1));
					_bl->pushPoint(PointMake(-1, 2));
					break;
				case 2:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(-2, 1));
					_bl->pushPoint(PointMake(-2, 2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(startX, startY + (i * 36), BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(1, -1));
					_bl->pushPoint(PointMake(2, -1));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(1, -2));
					_bl->pushPoint(PointMake(2, -2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}

			break;
		case 2:
			startX = x + 36;
			startY = y - 36;
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX - (i * 36), startY, BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(1, 1));
					_bl->pushPoint(PointMake(1, 2));
					break;
				case 2:
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					_bl->pushPoint(PointMake(2, 1));
					_bl->pushPoint(PointMake(2, 2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(startX, startY + (i * 36), BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(-1, -1));
					_bl->pushPoint(PointMake(-2, -1));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(-1, -2));
					_bl->pushPoint(PointMake(-2, -2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}

			break;
		case 3:
			startX = x - 36;
			startY = y + 36;
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX + (i * 36), startY, BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(-1, -1));
					_bl->pushPoint(PointMake(-1, -2));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 2:
					_bl->pushPoint(PointMake(-2, -1));
					_bl->pushPoint(PointMake(-2, -2));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(startX, startY - (i * 36), BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(1, 1));
					_bl->pushPoint(PointMake(2, 1));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, 2));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(1, 2));
					_bl->pushPoint(PointMake(2, 2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
			break;
		case 4:
			startX = x + 36;
			startY = y + 36;
			for (int i = 0; i < size; i++)
			{
				_bl = new block;
				_bl->init(startX - (i * 36), startY, BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(1, -1));
					_bl->pushPoint(PointMake(1, -2));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(1, 0));
					break;
				case 2:
					_bl->pushPoint(PointMake(2, -1));
					_bl->pushPoint(PointMake(2, -2));
					_bl->pushPoint(PointMake(1, 0));
					_bl->pushPoint(PointMake(2, 0));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
				_bl = new block;
				_bl->init(startX, startY - (i * 36), BLOCK_BLUE);
				switch (i)
				{
				case 0:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, -2));
					_bl->pushPoint(PointMake(-1, 0));
					_bl->pushPoint(PointMake(-2, 0));
					break;
				case 1:
					_bl->pushPoint(PointMake(0, -1));
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(-1, 1));
					_bl->pushPoint(PointMake(-2, 1));
					break;
				case 2:
					_bl->pushPoint(PointMake(0, 1));
					_bl->pushPoint(PointMake(0, 2));
					_bl->pushPoint(PointMake(-1, 2));
					_bl->pushPoint(PointMake(-2, 2));
					break;
				}
				_vBlock.push_back(make_pair(group, _bl));
			}
			break;
		}

		break;
	}
}

block * blockManager::getGroupBlock(int group)
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i].first == group)
		{
			return _vBlock[i].second;
		}
	}
	return nullptr;
}
