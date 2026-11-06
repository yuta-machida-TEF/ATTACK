
#pragma once

#include "Particle.h"
#include "Stage.h"
#include <KamataEngine.h>
#include <numbers>

using namespace KamataEngine;

class Enemy;
class Enemy2;

class Player {
public:
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update(Stage* stage, Enemy* enemy, Enemy2* enemy2);

	// 描画
	void Draw(Camera& camera);

	// 衝突判定
	bool CheckCollision(const WorldTransform& platform, const Vector3& platformSize, const Vector3& previousPosition);

	// Enemy・Enemy2共通の当たり判定
	bool CheckEnemyCollision(const WorldTransform& enemyTransform, const Vector3& enemySize, 
		                     const Vector3& previousPosition, Enemy* enemyObject, 
		                     Enemy2* enemyObject2);

	// ワールド変換を取得
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

private:
	// =========================
	// メンバ変数
	// =========================

	// モデル
	Model* model_ = nullptr;

	// パーティクル3Dモデルデータ
	Model* modelParticle_ = nullptr;

	// パーティクル
	std::list<Particle*> particles_;

	// 落下速度
	Vector2 velocity_ = {0.0f, 0.0f};

	// 重力
	const float gravity_ = -0.020f;

	// 地面にいるか
	bool isGround_ = true;

	// 地面の高さ
	const float groundY = -7.0f;

	// 前フレームの位置
	float previousBottom_ = 0.0f;

	// ジャンプ力
	const float jumpPower_ = 0.38f;

	// 移動速度
	const float moveSpeed_ = 0.20f;

	// 左右の移動方向
	float previousMoveDirection_ = 0.0f;

	// プレイヤーが生きているか
	bool isAlive_ = true;

	// ワールド変換
	WorldTransform worldTransform_;
};
