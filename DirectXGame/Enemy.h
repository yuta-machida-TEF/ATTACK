#pragma once

#include "EnemyBase.h"

class Enemy : public EnemyBase {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) override;

	void Update() override;
};