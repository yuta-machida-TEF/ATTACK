#pragma once
#include"PlayerState.h"
#include"Player.h"
#include"GameObject.h"


//Playerの移動処理
class PlayerMoveState : public PlayerState
{
public:
	void Update(Player& player) override;
};
