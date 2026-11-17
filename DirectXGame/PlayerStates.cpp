#include "PlayerStates.h"
#include "Player.h"

#include <numbers>

// 左右移動の共通処理
static void MovePlayer(Player& player) {

	auto* input = KamataEngine::Input::GetInstance();

	float direction = 0.0f;

	if (input->PushKey(DIK_RIGHT)) {
		direction = 1.0f;
	}

	if (input->PushKey(DIK_LEFT)) {
		direction = -1.0f;
	}

	if (direction != 0.0f) {

		player.worldTransform_.translation_.x += player.moveSpeed_ * direction;

		// 向きを変更
		if (direction != player.previousMoveDirection_) {

			player.worldTransform_.rotation_.y = direction > 0.0f ? std::numbers::pi_v<float> / 2.0f : -std::numbers::pi_v<float> / 2.0f;
		}

		player.previousMoveDirection_ = direction;
	}
}

// ========================================
// 待機状態
// ========================================

void PlayerIdleState::Update(Player& player) {

	auto* input = KamataEngine::Input::GetInstance();

	// ジャンプ
	if (input->TriggerKey(DIK_UP) && player.isGround_) {

		player.ChangeState(std::make_unique<PlayerJumpState>());

		return;
	}

	// 左右移動
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {

		player.ChangeState(std::make_unique<PlayerMoveState>());

		return;
	}
}

// ========================================
// 移動状態
// ========================================

void PlayerMoveState::Update(Player& player) {

	auto* input = KamataEngine::Input::GetInstance();

	// ジャンプ
	if (input->TriggerKey(DIK_UP) && player.isGround_) {

		player.ChangeState(std::make_unique<PlayerJumpState>());

		return;
	}

	// 移動
	player.Move();

	// 移動入力がない場合は待機
	if (!input->PushKey(DIK_RIGHT) && !input->PushKey(DIK_LEFT)) {

		player.ChangeState(std::make_unique<PlayerIdleState>());
	}
}

// ========================================
// ジャンプ状態
// ========================================

void PlayerJumpState::Enter(Player& player) {

	// ジャンプ開始
	player.velocity_.y = player.jumpPower_;

	player.isGround_ = false;
}

void PlayerJumpState::Update(Player& player) {

	auto* input = KamataEngine::Input::GetInstance();

	// 空中でも左右移動できる
	MovePlayer(player);

	// 着地したら状態変更
	if (player.isGround_) {

		if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {

			player.ChangeState(std::make_unique<PlayerMoveState>());

		} else {

			player.ChangeState(std::make_unique<PlayerIdleState>());
		}
	}
}

// ========================================
// 死亡状態
// ========================================

void PlayerDeadState::Update(Player& player) {

	// 死亡中は操作しない
}
