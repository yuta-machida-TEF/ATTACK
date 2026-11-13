
#pragma once

#include "EnemyBase.h"

class Enemy2 : public EnemyBase {
public:
	//Kill()、IsAlive()、GetWorldTransform()、GetSize() は親クラスから引き継ぐため、
	//Enemy.hに書く必要がありません。


	void Initialize(KamataEngine::Model* model);

};
