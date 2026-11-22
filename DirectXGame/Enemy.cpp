#include "Enemy.h"

using namespace KamataEngine;

void Enemy::Initialize(Model* model, Vector3 position) {

	// 基底クラスの初期化を利用
	EnemyBase::Initialize(model, position);

	velocityY_ = 0.0f;
	jumpTimer_ = 0.0f;
}

void Enemy::Update() {

	// ジャンプするまでの時間
	jumpTimer_ += 1.0f / 60.0f;

	// 接地していて、一定時間経過したらジャンプ
	if (isGround_ && jumpTimer_ >= 1.0f) {

		velocityY_ = jumpPower_;

		isGround_ = false;

		jumpTimer_ = 0.0f;
	}

	// 重力
	velocityY_ += gravity_;

	// Y座標を更新
	worldTransform_.translation_.y += velocityY_;

	// 地面判定
	if (worldTransform_.translation_.y <= groundY_) {

		worldTransform_.translation_.y = groundY_;

		velocityY_ = 0.0f;

		isGround_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(Camera& camera) { EnemyBase::Draw(camera); }