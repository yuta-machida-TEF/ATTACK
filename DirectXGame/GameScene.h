#pragma once

#include "Enemy.h"
#include "Enemy2.h"
#include "GameObject.h"
#include "ParticePool.h"
#include "Player.h"
#include "Stage.h"

#include <KamataEngine.h>
#include <vector>

using namespace KamataEngine;

class GameScene {
public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	// 3Dモデル
	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelEnemy2_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelParticle_ = nullptr;

	// 敵
	std::vector<EnemyBase*> enemies_;

	// オブジェクト管理
	std::vector<GameObject*> gameObjects_;

	// プレイヤー
	Player* player_ = nullptr;

	// ステージ
	Stage* stage_ = nullptr;

	// カメラ
	Camera camera_;

	// 内部処理用
	float previousBottom = 0.0f;

	Vector3 previousPosition = {-15.0f, 8.0f, 0.0f};

	std::vector<bool> previousEnemyAlive_;

	// Object Pool
	ParticlePool particlePool_;

	// パーティクル生成
	void CreateParticles(const Vector3& position);
};