#pragma once
#include "singletonBase.h"
class scoreData : public singletonBase<scoreData>
{
private:
	int _currentScore;
public:
	scoreData():_currentScore(0) {}
	~scoreData() {}

	void saveCurrentScore(int score)
	{
		_currentScore = score;
	}
	int loadCurrentScore()
	{
		return _currentScore;
	}

	void saveData(string fileName, int score);
	int loadData(string fileName);

};

