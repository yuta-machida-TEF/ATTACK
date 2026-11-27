#include "Enemy2.h"

// 初期化
void Enemy2::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) 
{ EnemyBase::Initialize(model, position); }

void Enemy2::Update() {

	if (!isAlive_) {
		return;
	}

	// EnemyBaseに共通する更新処理
	EnemyBase::Update();

	// Enemy独自の移動処理

	worldTransform_.UpdateMatrix();
}

void Enemy2::Draw(KamataEngine::Camera& camera) {
	if (isAlive_) {
		model_->Draw(worldTransform_, camera);
	}
}