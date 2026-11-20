#include "Enemy2.h"

// 初期化
void Enemy2::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) { EnemyBase::Initialize(model, position); }

void Enemy2::Update() {

	// Enemy独自の移動処理

	worldTransform_.UpdateMatrix();
}
