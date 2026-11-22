#pragma once

#include "PlayerState.h"

// 地上状態
class PlayerGroundedState : public PlayerState {
public:
	void Update(Player& player) override;
};

// ジャンプ状態
class PlayerJumpState : public PlayerState {
public:
	void Update(Player& player) override;
};

// 死亡状態
class PlayerDeadState : public PlayerState {
public:
	void Update(Player& player) override;
};