
#pragma once

#include "EnemyBase.h"
#include "GameObject.h"
#include "Stage.h"

#include <KamataEngine.h>
#include <memory>

class PlayerState;
class PlayerIdleState;
class PlayerMoveState;
class PlayerJumpState;
class PlayerDeadState;

class Player : public GameObject {
public:
	~Player();

	void Initialize(KamataEngine::Model* model);

	void Update(Stage* stage, EnemyBase* enemy, EnemyBase* enemy2);

	void Draw(KamataEngine::Camera& camera) override;

	bool CheckCollision(const KamataEngine::WorldTransform& platform, const KamataEngine::Vector3& platformSize, const KamataEngine::Vector3& previousPosition);

	bool CheckEnemyCollision(const KamataEngine::WorldTransform& enemyTransform, const KamataEngine::Vector3& enemySize, const KamataEngine::Vector3& previousPosition, EnemyBase* enemyObject);

	const KamataEngine::WorldTransform& GetWorldTransform() const override { return worldTransform_; }

	// 状態変更
	void ChangeState(std::unique_ptr<PlayerState> newState);

private:
	// 各StateクラスからPlayerのメンバ変数を利用する
	friend class PlayerIdleState;
	friend class PlayerMoveState;
	friend class PlayerJumpState;
	friend class PlayerDeadState;

	void Move();

	std::unique_ptr<PlayerState> state_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Vector2 velocity_ = {0.0f, 0.0f};

	const float gravity_ = -0.020f;

	bool isGround_ = true;

	const float groundY_ = -7.0f;

	float previousBottom_ = 0.0f;

	const float jumpPower_ = 0.38f;

	const float moveSpeed_ = 0.20f;

	float previousMoveDirection_ = 0.0f;

	bool isAlive_ = true;

	KamataEngine::WorldTransform worldTransform_;
};
