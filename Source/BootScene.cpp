#include "BootScene.h"
#include "../Library/SceneManager.h"

BootScene::BootScene()
{
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // �N�����I�������Title��\��
}

void BootScene::Draw()
{
}
