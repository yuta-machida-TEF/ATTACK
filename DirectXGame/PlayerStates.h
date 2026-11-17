#pragma once

#include "PlayerState.h"


// 待機状態
class PlayerIdleState : public PlayerState {
public:
	void Update(Player& player) override;
};

// 移動状態
class PlayerMoveState : public PlayerState {
public:
	void Update(Player& player) override;
};

// ジャンプ状態
class PlayerJumpState : public PlayerState {
public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
};

// 死亡状態
class PlayerDeadState : public PlayerState {
public:
	void Update(Player& player) override;
};
