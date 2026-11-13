
#include "Enemy.h"

// 初期化
void Enemy::Initialize(KamataEngine::Model* model) 
{ EnemyBase::Initialize(
	model,
	{10.0f, -3.0f, 0.0f}
   ); 
}
