#include "stdafx.h"
#include "image.h"

HRESULT image::init(int width, int height)
{
	if (_image) release();

	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = CreateCompatibleBitmap(hdc, width, height);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool trans, COLORREF color, int frameX, int frameY)
{

	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;
	_image->isTrans = trans;
	_image->color = color;

	if (frameX > 0 || frameY > 0)
	{
		_image->frameX = 0;
		_image->frameY = 0;
		_image->maxFrameX = frameX - 1;
		_image->maxFrameY = frameY - 1;
		_image->frameWidth = width / frameX;
		_image->frameHeight = height / frameY;
		_image->isFrame = true;
	}

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::blendImageInit()
{
	HDC hdc = GetDC(_hWnd);

	_blendImage = new tagImageInfo;
	_blendImage->hdc = CreateCompatibleDC(hdc);
	_blendImage->hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hdc, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	_blendFunction.AlphaFormat = 0;
	_blendFunction.BlendFlags = 0;
	_blendFunction.BlendOp = AC_SRC_OVER;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::tempImageInit()
{
	HDC hdc = GetDC(_hWnd);

	_tempImage = new tagImageInfo;
	_tempImage->hdc = CreateCompatibleDC(hdc);
	_tempImage->hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_tempImage->hOBit = (HBITMAP)SelectObject(_tempImage->hdc, _tempImage->hBit);
	_tempImage->width = WINSIZEX;
	_tempImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_image)
	{
		SelectObject(_image->hdc, _image->hOBit);
		DeleteObject(_image->hBit);
		DeleteDC(_image->hdc);
		SAFEDELETE(_image);
	}
	if (_tempImage)
	{
		SelectObject(_tempImage->hdc, _tempImage->hBit);
		DeleteObject(_tempImage->hBit);
		SAFEDELETE(_tempImage);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void image::render(HDC hdc, int deseX, int destY, int sizeX, int sizeY)
{

	
	GdiTransparentBlt(
		hdc,
		deseX,
		destY,
		sizeX,
		sizeY,
		_image->hdc,
		0, 0,
		_image->width,
		_image->height,
		_image->color
	);
	
	
}

void image::renderCenter(HDC hdc, int deseX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void image::renderCenter(HDC hdc, int deseX, int destY, int sizeX, int sizeY)
{
	GdiTransparentBlt(
		hdc,
		deseX - sizeX / 2,
		destY - sizeY / 2,
		sizeX,
		sizeY,
		_image->hdc,
		0, 0,
		_image->width,
		_image->height,
		_image->color
	);
}

void image::renderCenter(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - sourWidth/2,
			destY - sourHeight/2,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			sourWidth,
			sourHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			sourWidth,
			sourHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			SRCCOPY
		);
	}
}

void image::frameRenderCenter(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - _image->frameWidth/2,
			destY - _image->frameHeight/2,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX - _image->frameWidth/2,
			destY - _image->frameHeight/2,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			SRCCOPY
		);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//������(offset)�� �Ϲ������� ���� ������Ʈ �ȿ��� ������Ʈ ó������ �־��� ��ҳ� Ư�� ���������� ������
		//offset�� � Ư���� ������ �ణ ���̰� ���� �� �Ǵ� �� ���� ��ü�� �ǹ�(���̿� ���� ������)

		//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _image->width + (offsetX % _image->width);
	if (offsetY < 0) offsetY = _image->height + (offsetY % _image->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _image->height;
		rcSour.bottom = _image->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _image->width;
			rcSour.right = _image->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}


// size �κп� ��ǥ���ϴ� ��ǥ�� �Է�
void image::strechRender(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{

	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			sizeX,
			sizeY,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempImage->hdc,
			0, 0,
			sizeX, sizeY,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX, destY,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);

	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_image->hdc,
			0,
			0,
			_image->width,
			_image->height,
			SRCCOPY
		);
	}

}

void image::strechRender(HDC hdc, int destX, int destY, float size)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width * size,
			_image->height * size,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempImage->hdc,
			0, 0,
			_image->width * size,
			_image->height * size,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX, destY,
			_image->width * size,
			_image->height * size,
			_tempImage->hdc,
			0, 0,
			_image->width * size,
			_image->height * size,
			_image->color
		);

	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			_image->width * size,
			_image->height * size,
			_image->hdc,
			0,
			0,
			_image->width,
			_image->height,
			SRCCOPY
		);
	}
}

void image::strechRenderCenter(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			sizeX,
			sizeY,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempImage->hdc,
			0, 0,
			sizeX, sizeY,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX - sizeX /2, destY - sizeY/2,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);

	}
	else
	{
		StretchBlt(
			hdc,
			destX - sizeX /2,
			destY - sizeY /2,
			sizeX,
			sizeY,
			_image->hdc,
			0,
			0,
			_image->width,
			_image->height,
			SRCCOPY
		);
	}
}

void image::strechRenderCenter(HDC hdc, int destX, int destY, float size)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width * size,
			_image->height * size,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempImage->hdc,
			0, 0,
			_image->width * size,
			_image->height * size,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX - ((_image->width * size) /2), destY - ((_image->height * size) / 2),
			_image->width * size,
			_image->height * size,
			_tempImage->hdc,
			0, 0,
			_image->width * size,
			_image->height * size,
			_image->color
		);

	}
	else
	{
		StretchBlt(
			hdc,
			destX - ((_image->width * size) / 2),
			destY - ((_image->height * size) / 2),
			_image->width * size,
			_image->height * size,
			_image->hdc,
			0,
			0,
			_image->width,
			_image->height,
			SRCCOPY
		);
	}
}


//size�� ��ǥ���ϴ� ��ǥ �Է�
void image::strechFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY)
{

	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width,
			_image->height,
			hdc,
			0,
			0,
			SRCCOPY);

		StretchBlt(
			_tempImage->hdc, 0, 0,
			sizeX, sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY
		);
	}
}

void image::strechFrameRenderCenter(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width,
			_image->height,
			hdc,
			0,
			0,
			SRCCOPY);

		StretchBlt(
			_tempImage->hdc, 0, 0,
			sizeX, sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - sizeX /2,
			destY - sizeY /2,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX - sizeX / 2,
			destY - sizeY / 2,
			sizeX,
			sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY
		);
	}
}

void image::strechFrameRender(HDC hdc, int destX, int destY, float size, int frameX, int frameY)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	float sizeX = _image->frameWidth * size;
	float sizeY = _image->frameHeight * size;

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width,
			_image->height,
			hdc,
			0,
			0,
			SRCCOPY);

		StretchBlt(
			_tempImage->hdc, 0, 0,
			sizeX, sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY
		);
	}
}

void image::strechFrameRenderCenter(HDC hdc, int destX, int destY, float size, int frameX, int frameY)
{
	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	float sizeX = _image->frameWidth * size;
	float sizeY = _image->frameHeight * size;

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width,
			_image->height,
			hdc,
			0,
			0,
			SRCCOPY);

		StretchBlt(
			_tempImage->hdc, 0, 0,
			sizeX, sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - sizeX / 2,
			destY - sizeY / 2,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX - sizeX / 2,
			destY - sizeY / 2,
			sizeX,
			sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height, _image->hdc,
			0, 0, _image->width, _image->height, _image->color);

		GdiAlphaBlend(
			hdc, destX, destY,
			_image->width, _image->height, _blendImage->hdc, 0, 0, _image->width, _image->height, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _image->width, _image->height, _image->hdc, 0, 0, _image->width, _image->height, _blendFunction);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, int frameX, int frameY)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->frameWidth, _image->frameHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->frameWidth, _image->frameHeight, _image->hdc,
			_image->frameWidth * frameX, _image->frameHeight * frameY, _image->frameWidth, _image->frameHeight, _image->color);

		GdiAlphaBlend(
			hdc, destX, destY,
			_image->frameWidth, _image->frameHeight, _blendImage->hdc, 0, 0, _image->frameWidth, _image->frameHeight, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _image->frameWidth, _image->frameHeight, _image->hdc, _image->frameWidth * frameX, _image->frameHeight * frameY, _image->frameWidth, _image->frameHeight, _blendFunction);
	}
}

void image::alphaRenderCenter(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height,
			hdc,
			destX - _image->width/2, destY - _image->height /2, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height, _image->hdc,
			0, 0, _image->width, _image->height, _image->color);

		GdiAlphaBlend(
			hdc, destX - _image->width / 2, destY - _image->height / 2,
			_image->width, _image->height, _blendImage->hdc, 0, 0, _image->width, _image->height, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX - _image->width / 2, destY - _image->height / 2, _image->width, _image->height, _image->hdc, 0, 0, _image->width, _image->height, _blendFunction);
	}
}

void image::ASRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, BYTE alpha)
{
	if (!_tempImage) tempImageInit();
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{

	}
	else
	{
		BitBlt(
			_blendImage->hdc,
			0, 0,
			_image->width,
			_image->height,
			hdc,
			destX,
			destY,
			SRCCOPY);

		StretchBlt(
			_blendImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY);

		GdiAlphaBlend
		(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_blendImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_blendFunction);
	}
}

void image::ASFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY, BYTE alpha)
{
	if (!_tempImage) tempImageInit();
	if (!_blendImage) blendImageInit();

	if (_image->isTrans)
	{

	}
	else
	{

	}
}

void image::minimapRender(HDC hdc, int deseX, int destY, float size)
{
	if (!_tempImage) tempImageInit();

	BitBlt(
		_tempImage->hdc,
		0, 0,
		_image->width,
		_image->height,
		hdc,
		0, 0, SRCCOPY);

	BitBlt(
		hdc,
		deseX,
		destY,
		_image->width * size,
		_image->height * size,
		_tempImage->hdc,
		0, 0, SRCCOPY);

}

