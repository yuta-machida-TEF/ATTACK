#include "Enemy2.h"

// 初期化
void Enemy2::Initialize(KamataEngine::Model* model)
{ EnemyBase::Initialize(
	model, 
	{15.0f, -3.0f, 0.0f}
);
}
