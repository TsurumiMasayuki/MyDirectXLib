#pragma once
#include "Utility\State\IState.h"

class StateManager
{
public:
	virtual ~StateManager();
	//更新処理
	virtual void update();
	//ステートをセット
	virtual void setState(IState* newState);
	//ステートを強制的に変更(入口、出口処理は呼ばれない)
	void forceSetState(IState* newState);

protected:
	IState* m_pCurrentState;
};