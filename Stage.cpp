#include "Stage.h"
#include "./globals.h"
#include <stack>

// Stage���H
namespace StageMaze {
	std::stack<Point> prStack;

	void DigDug(int x, int y, vector<vector<STAGE_OBJ>>& _stage)
	{
		_stage[y][x] = STAGE_OBJ::EMPTY;
		Point Dir[]{ {0,-1},{1, 0},{0, 1},{-1,0} };
		std::vector<int> dList;
		for (int i = 0; i < 4; i++) {
			//next��0~3�܂ŉ񂵂Ăł��[���擾
			Point next = Point{ x + Dir[i].x, y + Dir[i].y };
			Point nextNext = { next.x + Dir[i].x, next.y + Dir[i].y };
			if (nextNext.x < 0 || nextNext.y < 0 || nextNext.x > STAGE_WIDTH - 1 || nextNext.y > STAGE_HEIGHT - 1)
				continue;

			if (_stage[nextNext.y][nextNext.x] == STAGE_OBJ::WALL)
			{
				dList.push_back(i);
			}
		}
		if (dList.empty())
		{
			return;
		}
		int nrand = rand() % dList.size();
		int tmp = dList[nrand];

		Point next = { x + Dir[tmp].x, y + Dir[tmp].y };
		Point nextNext = { next.x + Dir[tmp].x, next.y + Dir[tmp].y };

		_stage[next.y][next.x] = STAGE_OBJ::EMPTY;
		_stage[nextNext.y][nextNext.x] = STAGE_OBJ::EMPTY;

		prStack.push(nextNext);
		DigDug(nextNext.x, nextNext.y, _stage);
	}


	void AllWall(int w, int h, vector<vector<STAGE_OBJ>>& _stage)
	{
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++) {
				if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
					_stage[j][i] = STAGE_OBJ::EMPTY;
				else
					_stage[j][i] = STAGE_OBJ::WALL;
			}
		}
	}

	void MakeMazeDigDug(int w, int h, vector<vector<STAGE_OBJ>>& _stage)
	{
		AllWall(w, h, _stage);
		Point sp{ 1, 1 };
		prStack.push(sp);
		while (!prStack.empty())
		{
			sp = prStack.top();
			prStack.pop();
			DigDug(sp.x, sp.y, _stage);
		}
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
					_stage[j][i] = STAGE_OBJ::WALL;
				continue;
			}
		}
	}

}


Stage::Stage()
{

	stageData = vector(STAGE_HEIGHT, vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));

	StageMaze::MakeMazeDigDug(STAGE_WIDTH, STAGE_HEIGHT, stageData);
	setStageRects();
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			switch (stageData[y][x])
			{
			case STAGE_OBJ::EMPTY:
				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(132, 245, 110), TRUE);
				break;
			case STAGE_OBJ::WALL:
				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(159, 186, 113), TRUE);
				break;
			case STAGE_OBJ::GOAL:
				
				break;
			default:
				break;
			}
		}
	}
}

void Stage::setStageRects()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (stageData[y][x] == STAGE_OBJ::WALL)
			{
				stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
			}
		}
	}
}

Point Stage::GetRandomEmptyPosition()
{
	vector<Point> emptyPositions;
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (stageData[y][x] == STAGE_OBJ::EMPTY) {
				emptyPositions.push_back({ x * CHA_WIDTH, y * CHA_HEIGHT });
			}
		}
	}
	if (!emptyPositions.empty()) {
		int index = GetRand(emptyPositions.size());
		return emptyPositions[index];
	}
	return { CHA_WIDTH, CHA_HEIGHT };
}

bool Stage::IsPassable(int gridX, int gridY) {
	if (gridX < 0 || gridX >= STAGE_WIDTH || gridY < 0 || gridY >= STAGE_HEIGHT)
		return false;
	return stageData[gridY][gridX] == STAGE_OBJ::EMPTY;
}