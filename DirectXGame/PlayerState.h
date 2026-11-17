#pragma once

class Player;

class PlayerState {
public:
	virtual ~PlayerState() = default;

	// 状態に入ったとき
	virtual void Enter(Player& player) {}

	// 状態の更新
	virtual void Update(Player& player) = 0;
};
