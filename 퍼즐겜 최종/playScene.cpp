#include "stdafx.h"
#include "playScene.h"

HRESULT playScene::init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_block[i][j].x = 100 + (j * 36);
			_block[i][j].y = 120 + (i * 36);
			_block[i][j].rc = RectMakeCenter(_block[i][j].x, _block[i][j].y, 36, 36);
			_block[i][j].block = nullptr;
			_block[i][j].state = BLOCKTAIL_EMPTY;
			_block[i][j].frameTime = 0;
			_block[i][j].frameX = 0;
		}
	}

	_currentScore = 0;
	_highScore = scoreData::getSingleton()->loadData("score.txt");

	_count1 = 0;
	_count2 = 0;
	_count3 = 0;
	

	_bm = new blockManager;
	//_bm->setOMino(1, 120, WINSIZEY / 2 + 200, 3);
	//_bm->setOMino(2, 330, WINSIZEY / 2 + 200, 3);
	//_bm->setOMino(3, 540, WINSIZEY / 2 + 200, 3);

	setBlocks();

	return S_OK;
}

void playScene::release()
{
}

void playScene::update()
{
	if (_bm->getVBlock().size() == 0)
	{
		setBlocks();
	}

	if (INPUT->GetKeyDown('A'))
	{
		_bm->setOMino(5, 100, WINSIZEY / 2 + 100, 2);
	}
	
	for (int i = 0; i < 10; i++)
	{
		if (CheckWid(i))
		{
			_vCheckWid.push_back(i);
		}
		if (CheckHei(i))
		{
			_vCheckHei.push_back(i);
		}
	}

	if (_currentScore > _highScore)
	{
		_highScore = _currentScore;
	}
	
	for (int i = 0; i < _vCheckWid.size();)
	{
		for (int j = 0; j < 10; j++)
		{
			//_block[_vCheckWid[i]][j].isEmpty = true;
			_block[_vCheckWid[i]][j].state = BLOCKTAIL_POP;
			_block[_vCheckWid[i]][j].block->setIsPop(true);
			CheckCount();
		}
		_vCheckWid.erase(_vCheckWid.begin());
	}

	for (int i = 0; i < _vCheckHei.size(); )
	{
		for (int j = 0; j < 10; j++)
		{
			//_block[j][_vCheckHei[i]].isEmpty = true;
			_block[j][_vCheckHei[i]].state = BLOCKTAIL_POP;
			_block[j][_vCheckHei[i]].block->setIsPop(true);
			CheckCount();
		}
		_vCheckHei.erase(_vCheckHei.begin());
	}
	CheckCount();

	if (_count1 == 0 && _count2 == 0 && _count3 == 0)
	{
		if (_currentScore == _highScore)
		{
			scoreData::getSingleton()->saveData("score.txt", _currentScore);
		}
		scoreData::getSingleton()->saveCurrentScore(_currentScore);
		SCENEMANAGER->loadScene("resultSnene");
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (_block[i][j].state)
			{
			case BLOCKTAIL_FULL:
				_block[i][j].block->update();
				break;
			case BLOCKTAIL_EMPTY:
				break;
			case BLOCKTAIL_POP:
				_block[i][j].block->update();
				_block[i][j].frameTime += TIMEMANAGER->getElapsedTime();
				if (_block[i][j].frameTime > 0.1f)
				{
					_block[i][j].frameTime -= 0.1f;
					_block[i][j].frameX++;
					if (_block[i][j].frameX > 6)
					{
						_block[i][j].frameX = 0;
						_block[i][j].state = BLOCKTAIL_EMPTY;
					}
				}
				break;
			}

			
			
		}
	}

	
	

	
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		_bm->update(BLOCKMANAGER_IDLE);
	}
	if (INPUT->GetKey(VK_LBUTTON) && _bm->getBmState() != BLOCKMANAGER_NONUPDATE)
	{
		_bm->update(BLOCKMANAGER_MOVEBLOCK);
	}
	if (INPUT->GetKeyUp(VK_LBUTTON) && _bm->getBmState() == BLOCKMANAGER_MOVEBLOCK)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (PtInRect(&_block[i][j].rc, _ptMouse))
				{
					bool isFail = false;
					for (int k = 0; k < _bm->getCurrentBlock()->getVPoint().size(); k++)
					{
						POINT pt = _bm->getCurrentBlock()->getVPoint()[k];
						if (_block[i + pt.y][j + pt.x].state == BLOCKTAIL_FULL || i + pt.y > 9 || i + pt.y < 0 || j + pt.x > 9 || j + pt.x < 0	)
						{
							_bm->resetBlockPos(_bm->getCurrentGroup());
							isFail = true;
							break;
						}
					}

					if (!isFail)
					{
						_currentScore += _bm->getCurrentBlock()->getVPoint().size();
						CheckCount();
					}

					while (_bm->getCurrentBlock()->getVPoint().size() != 0)
					{
						if (isFail) break;
						POINT temp = _bm->getCurrentBlock()->getVPoint().back();
						_block[i + temp.y][j + temp.x].block = _bm->getCurrentBlock();
						
						_block[i + temp.y][j + temp.x].state = BLOCKTAIL_FULL;
						
						_bm->getCurrentBlock()->popPoint();
					}

					if(!isFail) _bm->popGroup(_bm->getCurrentGroup());
				}
				if (!PtInRect(&_block[i][j].rc, _ptMouse) && i == 9 && j == 9)
				{
					_bm->resetBlockPos(_bm->getCurrentGroup());
				}
			}
		}
		_bm->setBMState(BLOCKMANAGER_NONUPDATE);
	}
}

void playScene::render()
{
	IMAGEMANAGER->findImage("1020Logo")->renderCenter(getMemDC(), WINSIZEX / 2, 50);
	char temp[129];
	HFONT font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Hobo Bt");
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(temp, "score : %d", _currentScore);
	TextOut(getMemDC(), WINSIZEX / 2 + 135, 150, temp, strlen(temp));
	wsprintf(temp, "highScore : %d", _highScore);
	TextOut(getMemDC(), WINSIZEX / 2 + 70, 200, temp, strlen(temp));
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);

	

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (_block[i][j].state)
			{
			case BLOCKTAIL_EMPTY:
				IMAGEMANAGER->findImage("block_empty")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
				break;
			case BLOCKTAIL_FULL:
				//_block[i][j].block->getBlockIG()->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
				switch (_block[i][j].block->getColor())
				{
				case BLOCK_BLUE:
					IMAGEMANAGER->findImage("block_blue")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				case BLOCK_RED:
					IMAGEMANAGER->findImage("block_red")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				case BLOCK_YELLOW:
					IMAGEMANAGER->findImage("block_yellow")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				case BLOCK_PURPLE:
					IMAGEMANAGER->findImage("block_purple")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				case BLOCK_GREEN:
					IMAGEMANAGER->findImage("block_green")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				case BLOCK_PINK:
					IMAGEMANAGER->findImage("block_pink")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
					break;
				}
				break;
			case BLOCKTAIL_POP:
				//_block[i][j].block->getBlockIG()->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y,_block[i][j].frameX,0);
				IMAGEMANAGER->findImage("block_empty")->renderCenter(getMemDC(), _block[i][j].x, _block[i][j].y);
				switch (_block[i][j].block->getColor())
				{
				case BLOCK_BLUE:
					IMAGEMANAGER->findImage("blue_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				case BLOCK_RED:
					IMAGEMANAGER->findImage("red_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				case BLOCK_YELLOW:
					IMAGEMANAGER->findImage("yellow_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				case BLOCK_PURPLE:
					IMAGEMANAGER->findImage("purple_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				case BLOCK_GREEN:
					IMAGEMANAGER->findImage("green_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				case BLOCK_PINK:
					IMAGEMANAGER->findImage("pink_pop")->frameRenderCenter(getMemDC(), _block[i][j].x, _block[i][j].y, _block[i][j].frameX, 0);
					break;
				}
				break;
			}
		
		}
	}

	IMAGEMANAGER->findImage("blockBack")->render(getMemDC(), 60, WINSIZEY / 2 + 100);

	_bm->render();
}

void playScene::setBlocks()
{
	
	for (int i = 0; i < 3; i++)
	{
		switch (GetRandom(3))
		{
		case 0:
			_bm->setOMino(i+1, 120 + (i * 210), WINSIZEY / 2 + 200, GetRandom(2, 4));
			break;
		case 1:
			_bm->setIMino(i+1, 120 + (i * 210), WINSIZEY / 2 + 200, GetRandom(1, 6), GetRandom(2));
			break;
		case 2:
			_bm->setLMino(i+1, 120 + (i * 210), WINSIZEY / 2 + 200, GetRandom(2, 4), GetRandom(1, 5));
			break;
		}
	}

	CheckCount();
}

void playScene::CheckCount()
{
	_count1 = 0;
	_count2 = 0;
	_count3 = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_bm->getGroupBlock(1) != nullptr)
			{
				vector<POINT> pt = _bm->getGroupBlock(1)->getVPoint();
				if (!VCeckArea(i, j, pt))
				{
					_count1++;
				}

			}
			if (_bm->getGroupBlock(2) != nullptr)
			{
				vector<POINT> pt = _bm->getGroupBlock(2)->getVPoint();
				if (!VCeckArea(i, j, pt))
					_count2++;
			}
			if (_bm->getGroupBlock(3) != nullptr)
			{
				vector<POINT> pt = _bm->getGroupBlock(3)->getVPoint();
				if (!VCeckArea(i, j, pt))
					_count3++;
			}
		}
	}
}

bool playScene::CheckWid(int arr)
{
	for (int i = 0; i < 10; i++)
	{
		if (_block[arr][i].state == BLOCKTAIL_EMPTY)
		{
			return false;
		}
	}
	return true;
}

bool playScene::CheckHei(int arr)
{
	for (int i = 0; i < 10; i++)
	{
		if (_block[i][arr].state == BLOCKTAIL_EMPTY)
		{
			return false;
		}
	}
	return true;
}

bool playScene::CheckArea(int i, int j, POINT pt)
{
	if (_block[i + pt.y][j + pt.x].state != BLOCKTAIL_EMPTY || i + pt.y > 9 || i + pt.y < 0 || j + pt.x > 9 || j + pt.x < 0)
	{
		return true;
	}

	return false;
}

bool playScene::VCeckArea(int i, int j, vector<POINT> pt)
{
	for (int p = 0; p < pt.size(); p++)
	{
		if (CheckArea(i, j, pt[p]))
		{
			return true;
		}
	}
	return false;
}
