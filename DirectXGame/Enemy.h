#pragma once

#include "EnemyBase.h"

class Enemy : public EnemyBase {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) override;

	// 更新
	void Update() override;

	// 描画
	void Draw(KamataEngine::Camera& camera) override;

private:
	float jumpPower_ = 0.3f;
	float gravity_ = -0.02f;
	float velocityY_ = 0.0f;
	bool isGround_ = false;
	float jumpTimer_ = 0.0f;
};