
#include "Enemy.h"

void Enemy::Initialize(KamataEngine::Model* model,
	                   KamataEngine::Vector3 position) 
{ EnemyBase::Initialize(model, position); }

void Enemy::Update() {

	if (!isAlive_) {
		return;
	}
	
	//EnemyBaseに共通する更新処理
	EnemyBase::Update();

	// Enemy独自の移動処理をここに追加する

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(KamataEngine::Camera& camera) 
{
	if (isAlive_) {
		model_->Draw(worldTransform_, camera);
	}
}