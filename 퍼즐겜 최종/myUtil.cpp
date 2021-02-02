#include "stdafx.h"
#include "myUtil.h"

RECT MyUtil::RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}

RECT MyUtil::RectMake(int left, int top, int width, int height)
{
	RECT rc = { left, top,left + width,top + height };
	return rc;
}

void MyUtil::LineMake(HDC hdc, int startx, int starty, int endx, int endy)
{
	MoveToEx(hdc, startx, starty, NULL);
	LineTo(hdc, endx, endy);
}

void MyUtil::LineMake(HDC hdc, POINT start, POINT end)
{
	MoveToEx(hdc, start.x, start.y, NULL);
	LineTo(hdc, end.x, end.y);
}

void MyUtil::Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

void MyUtil::RectangleMake(HDC hdc, int left, int top, int wid, int height)
{
	Rectangle(hdc, left, top, left + wid, top + height);
}

void MyUtil::Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

int MyUtil::GetRandom(int num)
{
	return rand() % num;
}

int MyUtil::GetRandom(int from, int to)
{
	return rand() % (to - from) + from;
}

float MyUtil::GetRandom(float num)
{
	return (float)rand() / num;
}

float MyUtil::GetRandom(float from, float to)
{
	float rnd = (float)rand() / (float)RAND_MAX;
	return (rnd * (to - from) + from);
}

float MyUtil::GetDistance(float x1, float y1, float x2, float y2)
{
	float w = x2 - x1;
	float h = y2 - y1;
	float r = sqrt((w * w) + (h * h));
	return r;
}

float MyUtil::GetDistance(POINT start, POINT end)
{
	float w = start.x - end.x;
	float h = start.y - end.y;
	return sqrt((w*w) + (h*h));
}

float MyUtil::GetAngle(float x1, float y1, float x2, float y2)
{
	return -atan2(y2 - y1, x2 - x1);
}

POINT MyUtil::PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}
