#pragma once

/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X
/// </summary>
/// <author>N.Hanai</author>

#include <DxLib.h>
#include <string>
#include "SceneBase.h"
#include "ObjectManager.h"
#include "Time.h"

class GameObject
{
public:
	GameObject() : tag(""), destroy(false), dontDestroy(false), drawOrder(0) { ObjectManager::Push(this); }
	virtual ~GameObject() { ObjectManager::Pop(this); }

	/// <summary>
	/// ���t���[���̍X�V�����̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// ���t���[���̕`�揈���̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo���Ă�������
	/// �����Update�̑O�ɍ폜����܂�
	/// </summary>
	void DestroyMe() { destroy = true; }

	bool DestroyRequested() const { return destroy; }

	/// <summary>
	/// �V�[���`�F���W����Ƃ��ɁA�폜����Ȃ�����
	/// </summary>
	/// <param name="sw">�����Ȃ����true�Afalse�ɂ���ƍ폜�����</param>
	void StayOnSceneChange(bool sw = true) { dontDestroy = sw; }

	bool IsDontDestroy() const { return dontDestroy; }

	/// <summary>
	/// �`��̗D�揇�ʂ��w�肵�܂�
	/// ���l�������قǁA��ɕ`�悳���̂ŁA
	/// 2D�ł���΁A���ɕ\������܂�
	/// �����w�肵�Ȃ���΂O�ł�
	/// </summary>
	/// <param name="odr">�`�揇��</param>
	void SetDrawOrder(int order) {
		drawOrder = order;
		ObjectManager::SortByDrawOrder();
	}

	inline int GetDrawOrder() const {	return drawOrder; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// �w�肳�ꂽ�^�O�Ɠ�������Ԃ�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�����ł����true</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }
private:
	std::string tag;     // �^�O
	bool destroy;
	bool dontDestroy;
	int drawOrder;
};
