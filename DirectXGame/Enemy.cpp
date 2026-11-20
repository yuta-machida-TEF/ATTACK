
#include "Enemy.h"

void Enemy::Initialize(KamataEngine::Model* model,
	                   KamataEngine::Vector3 position) 
{ EnemyBase::Initialize(model, position); }

void Enemy::Update() {

	// Enemy独自の移動処理

	worldTransform_.UpdateMatrix();
}