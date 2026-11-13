
#include "EnemyBase.h"
#include <numbers>

// 初期化
void EnemyBase::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) {
	model_ = model;

	worldTransform_.Initialize();

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// 初期位置
	worldTransform_.translation_ = position;
}

// 更新
void EnemyBase::Update() {
	if (!isAlive_) {
		return;
	}

	// 重力計算
	velocity_.y += gravity_;

	worldTransform_.translation_.y += velocity_.y;

	// 地面判定
	if (worldTransform_.translation_.y <= groundY_) {

		worldTransform_.translation_.y = groundY_;

		velocity_.y = 0.0f;

		isGround_ = true;
	}

	worldTransform_.UpdateMatrix();
}

// 描画
void EnemyBase::Draw(KamataEngine::Camera& camera) {
	if (!isAlive_) {
		return;
	}

	if (model_ != nullptr) {
		model_->Draw(worldTransform_, camera);
	}
}

// 敵を倒す
void EnemyBase::Kill() {
	if (!isAlive_) {
		return;
	}

	isAlive_ = false;
}
