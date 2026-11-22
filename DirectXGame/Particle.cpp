
#include "Particle.h"
#include <algorithm>
#include <math/MathUtility.h>

using namespace MathUtility;

// 初期化
void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	velocity_ = velocity;

	// 大きさ
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	// 位置
	worldTransform_.translation_ = position;

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 色の設定
	color_ = {1, 1, 0, 1};

	// カウントをリセット
	counter_ = 0.0f;

	// フラグをリセット
	isFinished_ = false;
	isActive_ = true;
}

// 更新
void Particle::Update() {

	// 使用していない場合は何もしない
	if (!isActive_) {
		return;
	}

	// カウントを1フレーム分進める
	counter_ += 1.0f / 60.0f;

	// 存続時間に達した場合
	if (counter_ >= kDuration) {

		counter_ += kDuration;

		// 終了フラグ
		isFinished_ = true;

		// 使用終了
		isActive_ = false;

		return;
	}

	// フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();

	// 移動
	worldTransform_.translation_ += velocity_;
}

// 描画
void Particle::Draw(Camera& camera) {

	// 使用中でない場合は描画しない
	if (!isActive_) {
		return;
	}

	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}

// 使用終了
void Particle::Deactivate() {

	isActive_ = false;

	isFinished_ = true;
}
