#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init()
{
	_offsetX = 0;
	_offsetY = 0;

	_start = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 220, 74);
	_exit = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200,220, 74);

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	_offsetX++;
	_offsetY++;

	if (_offsetX > IMAGEMANAGER->findImage("mainBack")->getWidth())
	{
		_offsetX = 0;
	}
	if (_offsetY > IMAGEMANAGER->findImage("mainBack")->getHeight())
	{
		_offsetY = 0;
	}
	if (INPUT->GetKeyDown('Q'))
	{
		SCENEMANAGER->loadScene("2048Scene");
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_start, _ptMouse))
		{
			SCENEMANAGER->loadScene("playScene");
		}
		if (PtInRect(&_exit, _ptMouse))
		{
			PostQuitMessage(0);
		}
	}

}

void mainScene::render()
{
	IMAGEMANAGER->findImage("mainBack")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, _offsetY);

	IMAGEMANAGER->findImage("startButton")->render(getMemDC(), _start.left, _start.top);
	IMAGEMANAGER->findImage("exitButton")->render(getMemDC(), _exit.left, _exit.top);

	//Rectangle(getMemDC(), _start);
}
