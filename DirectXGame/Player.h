#pragma once

#include "EnemyBase.h"
#include "GameObject.h"
#include "Stage.h"
#include <KamataEngine.h>
#include"PlayerState.h"
#include<memory>

using namespace KamataEngine;

class Enemy;
class Enemy2;
class PlayerState;

//Stateクラスの前方宣言
class PlayerIdleState;
class PlayerMoveState;
class PlayerJumpState;
class PlayerDeadState;


class Player : public GameObject {
public:
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update(Stage* stage, const std::vector<EnemyBase*>& enemies);

	// 描画
	void Draw(KamataEngine::Camera& camera) override;

	// 衝突判定
	bool CheckCollision(const WorldTransform& platform, const Vector3& platformSize, const Vector3& previousPosition);

	// Enemy・Enemy2共通の当たり判定
	bool CheckEnemyCollision(const WorldTransform& enemyTransform, const Vector3& enemySize, const Vector3& previousPosition, EnemyBase* enemyObject);

	// ワールド変換を取得
	const WorldTransform& GetWorldTransform() const override { return worldTransform_; }

	 // 現在の状態を変更する
	void ChangeState(std::unique_ptr<PlayerState> newState);

	// 生存判定
	bool IsAlive() const { return isAlive_; }

private:
	// =========================
	// メンバ変数
	// =========================

	// モデル
	Model* model_ = nullptr;

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

	// 現在の状態
	std::unique_ptr<PlayerState> state_;

	// 次の状態
	std::unique_ptr<PlayerState> nextState_;

	// 状態クラスからPlayerの内部データを利用する
	friend class PlayerGroundedState;
	friend class PlayerJumpState;
	friend class PlayerDeadState;

	void UpdateHorizontalMove();
};