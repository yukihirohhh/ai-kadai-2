#include "Input.h"
#include "DxLib.h"

namespace Input {
	//�L�[�{�[�h�擾�֘A
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//�L�[�o�b�t�@ (���t���[��)
	char keyBuffOld[KEY_MAX];	//1�O�̃L�[�o�b�t�@(�O�t���[��) 
	char key_down[KEY_MAX];		//�����ꂽ�u�� 
	char key_up[KEY_MAX];		//�����ꂽ�u�� 
	char Key_Keep[KEY_MAX];		//�������ςȂ�
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//�S�ẴL�[�̏�Ԃ��擾 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//�O�t���[���ƌ��t���[����xor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//�����ꂽ�u�� = (���t���[����key_xor��AND) 
		key_up[i] = key_xor & keyBuffOld[i];	//�����ꂽ�u�� = (�O�t���[����key_xor��AND) 
	}
}

bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]);
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}