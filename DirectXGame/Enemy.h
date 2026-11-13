
#pragma once

#include "EnemyBase.h"

class Enemy : public EnemyBase {
public:
	//Kill()、IsAlive()、GetWorldTransform()、GetSize() は親クラスから引き継ぐため、
	// Enemy.hに書く必要がありません。


	void Initialize(KamataEngine::Model* model);

};
