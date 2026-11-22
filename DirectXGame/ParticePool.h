#pragma once

#include "Particle.h"

#include <KamataEngine.h>
#include <memory>
#include <vector>

class ParticlePool {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, int poolSize);

	// パーティクルを取得
	Particle* Acquire(KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// パーティクルを管理する配列
	std::vector<std::unique_ptr<Particle>> particles_;

	// パーティクルのモデル
	KamataEngine::Model* model_ = nullptr;
};
