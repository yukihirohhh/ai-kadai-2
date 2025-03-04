#pragma once

/// <summary>
/// �V�[���̊��N���X
/// </summary>
/// <author>N.Hanai</author>

#include <list>
#include "SceneManager.h"
#include "GameObject.h"

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Update() {}
	virtual void Draw() {}
};
