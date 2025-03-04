#include "Player.h"
#include "./Source/Input.h"
#include "./Stage.h"
#include "globals.h"
#include "ImGui/imgui.h"
#include "Enemy.h"
namespace {
	DIR inputDir = NONE;
}


Player::Player()
	: pos_({ CHA_WIDTH, CHA_HEIGHT }), playerImage_(-1)
{
}

Player::~Player()
{
}

void Player::Update()
{
	int ox = pos_.x, oy = pos_.y;

	if (Input::IsKeepKeyDown(KEY_INPUT_UP) || Input::IsKeepKeyDown(KEY_INPUT_W))
	{
		pos_.y--;
		inputDir = UP;
	}
	else if (Input::IsKeepKeyDown(KEY_INPUT_DOWN) || Input::IsKeepKeyDown(KEY_INPUT_S))
	{
		pos_.y++;
		inputDir = DOWN;
	}
	else if (Input::IsKeepKeyDown(KEY_INPUT_LEFT) || Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		pos_.x--;
		inputDir = LEFT;
	}
	else if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT) || Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		pos_.x++;
		inputDir = RIGHT;
	}

	Stage* stage = (Stage*)FindGameObject<Stage>();
	Rect playerRect = { pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT };

	for (auto& obj : stage->GetStageRects())
	{
		if (CheckHit(playerRect, obj))
		{
			Rect tmpRectX = { ox, pos_.y, CHA_WIDTH, CHA_HEIGHT };
			Rect tmpRecty = { pos_.x, oy, CHA_WIDTH, CHA_HEIGHT };
			//x�������ň����|������
			if (!CheckHit(tmpRectX, obj))
			{
				pos_.x = ox;//x�������ɂ߂荞�ݏC��
				//�ǃY��
				Point centerMe = Rect{ pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.y > centerObj.y)
				{
					pos_.y++;
				}
				if (centerMe.y < centerObj.y)
				{
					pos_.y--;
				}
			}
			else if (!CheckHit(tmpRecty, obj))
			{
				pos_.y = oy;//y�����Ɉ�������������߂荞�ݏC��
				//�ǃY��
				Point centerMe = Rect{ pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.x > centerObj.x)
				{
					pos_.x++;
				}
				if (centerMe.x < centerObj.x)
				{
					pos_.x--;
				}
			}
			else
			{
				//����ȊO�ň����|��������
				pos_.x = ox;
				pos_.y = oy;
				break; // �ǂɓ���������ړ����L�����Z��
			}
		}
	}
}

void Player::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT, GetColor(255, 10, 10), TRUE);
}

bool Player::CheckHit(const Rect& me, const Rect& other)
{
	if (me.x < other.x + other.w && me.x + me.w > other.x && me.y < other.y + other.h && me.y + me.h > other.y) {
		return true;
	}
	return false;
}



