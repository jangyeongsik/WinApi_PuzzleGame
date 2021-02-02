#include "stdafx.h"
#include "result_2048.h"


HRESULT result_2048::init()
{
	_y = 0;
	_state = RESULT2048STATE::RESULTBOXDOWN;

	_regam = RectMake(WINSIZEX / 2 - 168, WINSIZEY / 2 + 73, 128, 104);
	_quit = RectMake(WINSIZEX / 2 + 40, WINSIZEY / 2 + 73, 128, 104);

	_hi = scoreData::getSingleton()->loadData("2048.txt");
	_sco = scoreData::getSingleton()->loadCurrentScore();

	return S_OK;
}

void result_2048::release()
{
}

void result_2048::update()
{

	switch (_state)
	{
	case RESULT2048STATE::RESULTBOXDOWN:
		_y += 2;
		if (_y > WINSIZEY / 2)
		{
			_state = RESULT2048STATE::RESULTSELECT;
		}
		break;
	case RESULT2048STATE::RESULTSELECT:
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_regam, _ptMouse))
			{
				SCENEMANAGER->loadScene("playScene");
			}
			if (PtInRect(&_quit, _ptMouse))
			{
				PostQuitMessage(0);
			}
		}
		break;
	}

}

void result_2048::render()
{
	Rectangle(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 - 200, WINSIZEX / 2 + 200, WINSIZEY / 2 + 200);
	IMAGEMANAGER->findImage("result")->renderCenter(getMemDC(), WINSIZEX / 2, _y);

	SetBkMode(getMemDC(), 1);
	char temp[128];
	HFONT font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Hobo Bt");
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(temp, "HIGHSCORE : %d", _hi);
	TextOut(getMemDC(), WINSIZEX / 2 - 100, _y - 50, temp, strlen(temp));
	wsprintf(temp, "SCORE : %d", _sco);
	TextOut(getMemDC(), WINSIZEX / 2 - 100, _y, temp, strlen(temp));

	SelectObject(getMemDC(), oFont);
	DeleteObject(font);

}
