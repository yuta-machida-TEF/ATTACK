#pragma once

#include "EnemyBase.h"

class Enemy2 : public EnemyBase {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) override;

	void Update() override;

	void Draw(KamataEngine::Camera& camera) override;
};