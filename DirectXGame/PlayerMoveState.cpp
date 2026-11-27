#include "PlayerMoveState.h"


void PlayerMoveState::Update(Player& player)
{
	// ========================================================
	// ③ 左右移動・旋回
	// ========================================================

	// 移動方向
	float moveDirection = 0.0f;

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		worldTransform_.translation_.x += moveSpeed_;
		moveDirection = 1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		worldTransform_.translation_.x -= moveSpeed_;
		moveDirection = -1.0f;
	}

	// 移動方向が変わったらプレイヤーの向きを変更する
	if (moveDirection != 0.0f && moveDirection != previousMoveDirection_) {

		if (moveDirection > 0.0f) {
			// 右を向く
			worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
		} else {
			// 左を向く
			worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;
		}
	}

	// 移動している場合だけ、方向を記録する
	if (moveDirection != 0.0f) {
		previousMoveDirection_ = moveDirection;
	}
}
