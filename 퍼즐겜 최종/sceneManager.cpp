#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	/*miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		if (iter->second != nullptr)
		{
			if (iter->second == _currentScene)
			{
				iter->second->release();
				SAFEDELETE(iter->second);
				iter = _mSceneList.erase(iter);
			}
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();*/

	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFEDELETE(scene.second);
	}

}

void sceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render()
{
	if (_currentScene)
	{
		_currentScene->render();
	}
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}

	if (find->second == _currentScene)
	{
		return E_FAIL;
	}

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_NOTIMPL;
}
