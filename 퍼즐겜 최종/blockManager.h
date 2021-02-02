#pragma once
#include "gameNode.h"
#include "block.h"


typedef enum BLOCKMANAGERUPDATESTATE
{
	BLOCKMANAGER_IDLE,
	BLOCKMANAGER_MOVEBLOCK,
	BLOCKMANAGER_NONUPDATE
}BMSTATE;

class blockManager : public gameNode
{
private:
	vector<pair<int, block*>> _vBlock;
private:
	int _currentMoveGroup;
	int _currentMoveIndex;
	BMSTATE _bmState;
public:
	blockManager() :_bmState(BLOCKMANAGER_NONUPDATE) {}
	~blockManager() {}

	void update(BMSTATE bs);
	void render();

	void popGroup(int group);
	void resetBlockPos(int group);

	void setOMino(int group, float x, float y, int size);
	void setIMino(int group, float x, float y, int size, bool location = true);

	// 1: LT	2: RT	3: LB	4: RB
	void setLMino(int group, float x, float y, int size, int angle);
	BMSTATE getBmState() { return _bmState; }
	void setBMState(BMSTATE bs) { _bmState = bs; }
	int getCurrentGroup() { return _currentMoveGroup; }
	block* getCurrentBlock() { return _vBlock[_currentMoveIndex].second; }
	block* getGroupBlock(int group);
	vector<pair<int, block*>> getVBlock() { return _vBlock; }
	void popVBlock(int arr) { _vBlock.erase(_vBlock.begin() + arr); }
};



