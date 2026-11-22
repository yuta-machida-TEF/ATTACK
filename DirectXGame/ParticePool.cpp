#include "ParticePool.h"

// 初期化
void ParticlePool::Initialize(KamataEngine::Model* model, int poolSize) {

	assert(model);

	model_ = model;

	// プールの初期化
	particles_.clear();

	// あらかじめパーティクルを生成
	for (int i = 0; i < poolSize; i++) {

		auto particle = std::make_unique<Particle>();

		// 仮の位置・速度で初期化
		particle->Initialize(model_, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

		// 使用していない状態にする
		particle->Deactivate();

		particles_.push_back(std::move(particle));
	}
}

// パーティクルを取得
Particle* ParticlePool::Acquire(KamataEngine::Vector3 position, KamataEngine::Vector3 velocity) {

	// 未使用のパーティクルを探す
	for (auto& particle : particles_) {

		if (!particle->IsActive()) {

			// 再初期化して使用する
			particle->Initialize(model_, position, velocity);

			return particle.get();
		}
	}

	// 使用可能なパーティクルがない
	return nullptr;
}

// 更新
void ParticlePool::Update() {

	for (auto& particle : particles_) {

		if (particle->IsActive()) {

			particle->Update();
		}
	}
}

// 描画
void ParticlePool::Draw(KamataEngine::Camera& camera) {

	for (auto& particle : particles_) {

		if (particle->IsActive()) {

			particle->Draw(camera);
		}
	}
}
