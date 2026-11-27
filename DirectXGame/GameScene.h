#pragma once
#include "Particle.h"
#include "Player.h"
#include "Stage.h"
#include"GameObject.h"
#include"Enemy.h"
#include"Enemy2.h"
#include"EnemyBase.h"
#include <KamataEngine.h>
#include <vector>

using namespace KamataEngine;

class GameScene {
public:
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// =========================
	// 3Dモデル
	// =========================

	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelEnemy2_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelParticle_ = nullptr;

	// =========================
	// オブジェクト
	// =========================

	//=========================
	// 敵
	// ========================
	 // 敵をまとめて管理する配列
	std::vector<EnemyBase*> enemies_;



	// 描画するオブジェクトをまとめる
	// ポリモーフィズムで管理するオブジェクト
	std::vector<GameObject*> gameObjects_;

    //=======================
	//プレイヤー
	//=======================
	Player* player_ = nullptr;
	//=======================
	//ステージ
	//=======================
	Stage* stage_ = nullptr;
	//=======================
	//パーティクル
	//=======================
	Particle* particle_ = nullptr;

	// =========================
	// カメラ
	// =========================

	Camera camera_;

	// =========================
	// 内部処理用の変数
	// =========================

	float previousBottom = 0.0f;

	Vector3 previousPosition = {-15.0f, 8.0f, 0.0f};

	std::vector<bool> previousEnemyAlive_;

	// =========================
	// パーティクル
	// =========================

	std::vector<Particle*> particles_;
	

	// =========================
	// 内部処理用関数
	// =========================

	void CreateParticles(const Vector3& position);
};
