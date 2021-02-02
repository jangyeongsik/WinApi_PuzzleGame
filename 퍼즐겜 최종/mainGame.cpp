#include "stdafx.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init();
	imageInit();

	SCENEMANAGER->addScene("mainScene", new mainScene);
	SCENEMANAGER->addScene("playScene", new playScene);
	SCENEMANAGER->addScene("2048Scene", new PLAYSCENE);
	SCENEMANAGER->addScene("resultSnene", new resultScene);
	SCENEMANAGER->addScene("2048result", new result_2048);
	SCENEMANAGER->loadScene("mainScene");



	return S_OK;
}

void mainGame::release()
{

	gameNode::release();

}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();



	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void mainGame::imageInit()
{
	IMAGEMANAGER->addImage("block_empty", "image/block_empty.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_red", "image/block_red.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_blue", "image/block_blue.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_green", "image/block_green.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_yellow", "image/block_yellow.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_pink", "image/block_pink.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("block_purple", "image/block_purple.bmp", 30, 30, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1020Logo", "image/1020Logo.bmp", 215, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainBack", "image/mainBack.bmp", 800, 727, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startButton", "image/startButton.bmp", 220, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("exitButton", "image/exitButton.bmp", 220, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blockBack", "image/blocksBack.bmp", 600, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blue_pop", "image/blue_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("red_pop", "image/red_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("pink_pop", "image/pink_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("green_pop", "image/green_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("yellow_pop", "image/yellow_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("purple_pop", "image/purple_pop.bmp", 280, 30, true, RGB(255, 0, 255), 7, 1);
	IMAGEMANAGER->addImage("result", "image/result.bmp", 400, 400, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("base", "image/base.bmp", 370, 370, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "image/2.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "image/4.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "image/8.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("16", "image/16.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("32", "image/32.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("64", "image/64.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("128", "image/128.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("256", "image/256.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("512", "image/512.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1024", "image/1024.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2048", "image/2048.bmp", 80, 80, false, RGB(255, 0, 255));
}
