#pragma once

namespace MyUtil
{
	
	RECT RectMakeCenter(int x, int y, int width, int height);
	RECT RectMake(int left, int top, int width, int height);
	void LineMake(HDC hdc, int startx, int starty, int endx, int endy);
	void LineMake(HDC hdc, POINT start, POINT end);
	void Rectangle(HDC hdc, RECT rc);
	void RectangleMake(HDC hdc, int left, int top, int wid, int height);
	void Ellipse(HDC hdc, RECT rc);
	int GetRandom(int num);
	int GetRandom(int from, int to);
	float GetRandom(float num);
	float GetRandom(float from, float to);
	float GetDistance(float x1, float y1, float x2, float y2);
	float GetDistance(POINT start, POINT end);
	float GetAngle(float x1, float y1, float x2, float y2);
	POINT PointMake(int x, int y);


}

