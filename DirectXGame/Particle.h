
#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Particle {
public:
	// 終了フラグのgetter
	bool IsFinished() const { return isFinished_; }

	// 使用中かどうか
	bool IsActive() const { return isActive_; }

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// 使用終了
	void Deactivate();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 色の数値
	KamataEngine::Vector4 color_;

	// 移動量
	KamataEngine::Vector3 velocity_;

	// 終了フラグ
	bool isFinished_ = true;

	// 使用中フラグ
	bool isActive_ = false;

	// 経過時間カウント
	float counter_ = 0.0f;

	// 存続時間
	const float kDuration = 1.0f;
};
