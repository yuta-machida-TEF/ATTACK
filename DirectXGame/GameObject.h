#pragma once

#include <KamataEngine.h>

class GameObject {
public:
	// 仮想デストラクタ
	// virtuaとは、子クラスで関数を上書きできるようにするための指定のこと
	// ポリモーフィズムは、単にコードを短くするためだけではなく、
	// 敵やキャラクターの種類が増えても管理しやすいゲーム設計にするために使います。
	virtual ~GameObject() = default;

	// 描画関数
	virtual void Draw(KamataEngine::Camera& camera) = 0;

	// ワールド変換取得
	//この関数は、メンバー変数を変更しないことを保証する関数です。
	virtual const KamataEngine::WorldTransform& GetWorldTransform() const = 0;
};