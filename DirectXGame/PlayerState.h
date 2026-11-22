#pragma once

class Player;

// 状態クラスの共通インターフェース
class PlayerState {
public:
	virtual ~PlayerState() = default;

	// 状態ごとの更新処理
	virtual void Update(Player& player) = 0;
};