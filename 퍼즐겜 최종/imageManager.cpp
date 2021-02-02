#include "stdafx.h"
#include "imageManager.h"

image * imageManager::addImage(string key, int width, int height)
{
	image* img = findImage(key);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImage.insert(make_pair(key, img));

	return img;
}

image * imageManager::addImage(string key, const char * fileName, int width, int height, bool trans, COLORREF color, int frameX, int frameY)
{
	image* img = findImage(key);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, trans, color,frameX,frameY)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImage.insert(make_pair(key, img));

	return img;
}

image * imageManager::findImage(string key)
{
	mImageIter _key = _mImage.find(key);

	if (_key != _mImage.end())
	{
		return _key->second;
	}

	return nullptr;
}

bool imageManager::deleteImage(string key)
{
	mImageIter _key = _mImage.find(key);

	//�˻��� Ű�� ã�Ҵٸ� �̹����� ��������
	if (_key != _mImage.end())
	{
		//�̹��� ����
		_key->second->release();
		//�޸� ����
		SAFE_DELETE(_key->second);
		//���� �ݺ��� ����
		_mImage.erase(_key);

		return true;
	}

	return false;
}

void imageManager::clearImage()
{
	_mImage.clear();
}
