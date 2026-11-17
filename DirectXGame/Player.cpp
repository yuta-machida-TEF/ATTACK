#include "Player.h"
#include"EnemyBase.h"

#include <math/MathUtility.h>
#include<numbers>

#include"PlayerStates.h"
#include<memory>

using namespace KamataEngine;
using namespace MathUtility;

//GameScene側でパーティクルの生成と描画、削除を管理している
Player::~Player()
{
	
}

// 初期化
void Player::Initialize(Model* model) {

	model_ = model;

	worldTransform_.Initialize();

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	//std::unique_ptrは自動でメモリを解放する
	//注意点は、同じオブジェクトを複数を所有することができない
	ChangeState(std::make_unique<PlayerIdleState>());

}

void Player::ChangeState(std::unique_ptr<PlayerState> newState) {

	state_ = std::move(newState);

	if (state_) {
		state_->Enter(*this);
	}
}

// ============================================================
// 足場との全方向当たり判定
// ============================================================

bool Player::CheckCollision(const KamataEngine::WorldTransform& platform, const KamataEngine::Vector3& platformSize, const KamataEngine::Vector3& previousPosition) {

	// ========================================================
	// プレイヤーの大きさ
	// ========================================================

	const float playerHalfWidth = 0.5f;
	const float playerHalfHeight = 0.5f;
	const float playerHalfDepth = 0.5f;

	// ========================================================
	// 現在のプレイヤーの位置
	// ========================================================

	const float playerX = worldTransform_.translation_.x;

	const float playerY = worldTransform_.translation_.y;

	const float playerZ = worldTransform_.translation_.z;

	// 現在のプレイヤーの範囲

	const float playerLeft = playerX - playerHalfWidth;

	const float playerRight = playerX + playerHalfWidth;

	const float playerBottom = playerY - playerHalfHeight;

	const float playerTop = playerY + playerHalfHeight;

	const float playerFront = playerZ - playerHalfDepth;

	const float playerBack = playerZ + playerHalfDepth;

	// ========================================================
	// 前フレームのプレイヤーの範囲
	// ========================================================

	const float previousLeft = previousPosition.x - playerHalfWidth;

	const float previousRight = previousPosition.x + playerHalfWidth;

	const float previousBottom = previousPosition.y - playerHalfHeight;

	const float previousTop = previousPosition.y + playerHalfHeight;

	const float previousFront = previousPosition.z - playerHalfDepth;

	const float previousBack = previousPosition.z + playerHalfDepth;

	// ========================================================
	// 足場の範囲
	// ========================================================

	const float platformX = platform.translation_.x;

	const float platformY = platform.translation_.y;

	const float platformZ = platform.translation_.z;

	const float platformHalfX = platformSize.x / 2.0f;

	const float platformHalfY = platformSize.y / 2.0f;

	const float platformHalfZ = platformSize.z / 2.0f;

	const float platformLeft = platformX - platformHalfX;

	const float platformRight = platformX + platformHalfX;

	const float platformBottom = platformY - platformHalfY;

	const float platformTop = platformY + platformHalfY;

	const float platformFront = platformZ - platformHalfZ;

	const float platformBack = platformZ + platformHalfZ;

	// ========================================================
	// 現在の重なり
	// ========================================================

	const bool overlapX = playerRight > platformLeft && playerLeft < platformRight;

	const bool overlapY = playerTop > platformBottom && playerBottom < platformTop;

	const bool overlapZ = playerBack > platformFront && playerFront < platformBack;

	// ========================================================
	// 上面に着地
	// ========================================================

	if (overlapX && overlapZ && previousBottom >= platformTop && playerBottom <= platformTop && velocity_.y <= 0.0f) {

		worldTransform_.translation_.y = platformTop + playerHalfHeight;

		velocity_.y = 0.0f;

		

		isGround_ = true;

		return true;
	}

	// ========================================================
	// 左面に衝突
	// ========================================================

	if (overlapY && overlapZ && previousRight <= platformLeft && playerRight >= platformLeft) {

		worldTransform_.translation_.x = platformLeft - playerHalfWidth;

		return true;
	}

	// ========================================================
	// 右面に衝突
	// ========================================================

	if (overlapY && overlapZ && previousLeft >= platformRight && playerLeft <= platformRight) {

		worldTransform_.translation_.x = platformRight + playerHalfWidth;

		return true;
	}

	// ========================================================
	// 前面に衝突
	// ========================================================

	if (overlapX && overlapY && previousBack <= platformFront && playerBack >= platformFront) {

		worldTransform_.translation_.z = platformFront - playerHalfDepth;

		return true;
	}

	// ========================================================
	// 背面に衝突
	// ========================================================

	if (overlapX && overlapY && previousFront >= platformBack && playerFront <= platformBack) {

		worldTransform_.translation_.z = platformBack + playerHalfDepth;

		return true;
	}

	// ========================================================
	// 底面に衝突
	// ========================================================

	if (overlapX && overlapZ && previousTop <= platformBottom && playerTop >= platformBottom && velocity_.y > 0.0f) {

		worldTransform_.translation_.y = platformBottom - playerHalfHeight;

		velocity_.y = 0.0f;

		return true;
	}

	return false;
}


void Player::Move() {

	auto* input = Input::GetInstance();

	float direction = 0.0f;

	if (input->PushKey(DIK_RIGHT)) {
		direction = 1.0f;
	}

	if (input->PushKey(DIK_LEFT)) {
		direction = -1.0f;
	}

	if (direction != 0.0f) {

		worldTransform_.translation_.x += moveSpeed_ * direction;

		if (direction != previousMoveDirection_) {

			worldTransform_.rotation_.y = direction > 0.0f ? std::numbers::pi_v<float> / 2.0f : -std::numbers::pi_v<float> / 2.0f;
		}

		previousMoveDirection_ = direction;
	}
}

//============================================================
//敵の当たり判定
//============================================================

//============================================================
// Enemy・Enemy2共通の当たり判定
//============================================================
bool Player::CheckEnemyCollision(
	const WorldTransform& enemyTransform,
	const Vector3& enemySize,
	const Vector3& previousPosition,
	EnemyBase* enemyObject) {

	
	//============================================================
	// Playerの大きさ
	//============================================================

	const float playerHalfWidth = 0.5f;
	const float playerHalfHeight = 0.5f;
	const float playerHalfDepth = 0.5f;

	//============================================================
	// Enemyの大きさ
	//============================================================

	const float enemyHalfWidth = enemySize.x / 2.0f;
	const float enemyHalfHeight = enemySize.y / 2.0f;
	const float enemyHalfDepth = enemySize.z / 2.0f;

	//============================================================
	// Playerの現在位置
	//============================================================

	const float playerX = worldTransform_.translation_.x;
	const float playerY = worldTransform_.translation_.y;
	const float playerZ = worldTransform_.translation_.z;

	const float playerLeft = playerX - playerHalfWidth;
	const float playerRight = playerX + playerHalfWidth;

	const float playerBottom = playerY - playerHalfHeight;
	const float playerTop = playerY + playerHalfHeight;

	const float playerFront = playerZ - playerHalfDepth;
	const float playerBack = playerZ + playerHalfDepth;

	//============================================================
	// Playerの前フレーム位置
	//============================================================

	const float previousBottom = previousPosition.y - playerHalfHeight;

	//============================================================
	// Enemyの範囲
	//============================================================

	const float enemyX = enemyTransform.translation_.x;
	const float enemyY = enemyTransform.translation_.y;
	const float enemyZ = enemyTransform.translation_.z;

	const float enemyLeft = enemyX - enemyHalfWidth;
	const float enemyRight = enemyX + enemyHalfWidth;

	const float enemyBottom = enemyY - enemyHalfHeight;
	const float enemyTop = enemyY + enemyHalfHeight;

	const float enemyFront = enemyZ - enemyHalfDepth;
	const float enemyBack = enemyZ + enemyHalfDepth;

	//============================================================
	// X・Y・Zの重なり
	//============================================================

	const bool overlapX = playerRight > enemyLeft && playerLeft < enemyRight;

	const bool overlapY = playerTop > enemyBottom && playerBottom < enemyTop;

	const bool overlapZ = playerBack > enemyFront && playerFront < enemyBack;

	//============================================================
	// ① 敵の頭を踏んだ
	//============================================================

	if (overlapX && overlapZ && previousBottom >= enemyTop && playerBottom <= enemyTop && velocity_.y <= 0.0f) {

		// Playerを敵の頭の上に移動
		worldTransform_.translation_.y = enemyTop + playerHalfHeight;

		// Playerを跳ねさせる
		velocity_.y = jumpPower_;

		// 対象の敵を倒す
	    enemyObject->Kill();
		

		isGround_ = false;

		ChangeState(std::make_unique<PlayerJumpState>());

		return true;
	}

	//============================================================
	// ② 横・下から敵に衝突
	//============================================================

	if (overlapX && overlapY && overlapZ) {

		isAlive_ = false;

		ChangeState(std::make_unique<PlayerDeadState>());

		return true;
	}

	return false;
}

// ============================================================
// 更新
// ============================================================


void Player::Update(Stage* stage, EnemyBase* enemy, EnemyBase* enemy2) {

	// ① 前フレームの位置を保存
	const Vector3 previousPosition = worldTransform_.translation_;

	// ② 死亡していたら更新しない
	if (!isAlive_) {
		return;
	}

	// ③ Stateを更新
	if (state_) {
		state_->Update(*this);
	}

	// ④ 接地状態を解除
	isGround_ = false;

	// ⑤ 重力
	velocity_.y += gravity_;

	worldTransform_.translation_.y += velocity_.y;

	// ⑥ 足場との当たり判定
	for (int y = 0; y < Stage::kMapHeight; y++) {
		for (int x = 0; x < Stage::kMapWidth; x++) {

			if (stage->GetMapData(y, x) == 1) {

				CheckCollision(stage->GetWorldTransform(y, x), stage->GetPlatformSize(), previousPosition);
			}
		}
	}

	// ⑦ 敵との当たり判定
	if (enemy != nullptr && enemy->IsAlive()) {

		CheckEnemyCollision(enemy->GetWorldTransform(), enemy->GetSize(), previousPosition, enemy);
	}

	// ⑧ Enemy2との当たり判定
	if (enemy2 != nullptr && enemy2->IsAlive()) {

		CheckEnemyCollision(enemy2->GetWorldTransform(), enemy2->GetSize(), previousPosition, enemy2);
	}

	// ⑨ ワールド行列更新
	worldTransform_.UpdateMatrix();
}


// ============================================================
// 描画
// ============================================================

void Player::Draw(Camera& camera)
{
    if (!isAlive_) {
        return;
    }

    model_->Draw(worldTransform_, camera);
}