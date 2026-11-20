#pragma once

#include "EnemyBase.h"

//ポリモーフィズムを使用
class Enemy : public EnemyBase {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) override;

	void Update() override;
		
	void Draw(KamataEngine::Camera& camera) override;
};