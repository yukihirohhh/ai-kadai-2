#pragma once


	struct Point
	{
		int x, y;

		// ������r���Z�q
		bool operator==(const Point& other) const {
			return x == other.x && y == other.y;
		}

		// �s����r���Z�q
		bool operator!=(const Point& other) const {
			return !(*this == other);
		}

		// C2676�@�G���[���o��̂ŁA�A�A
		bool operator<(const Point& other) const {
			return (x < other.x) || (x == other.x && y < other.y);
		}

	};

	struct Pointf
	{
		float x, y;
	};

	struct Rect
	{
		int x, y, w, h;
		Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
		Point GetCenter() { return Point{ x + w / 2, y + h / 2 }; }
	};


	enum class STAGE_OBJ {
		EMPTY,
		WALL,
		GOAL,
		MAX_OBJECT
	};


	enum DIR
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		MAXDIR
	};
	
	const int CHA_WIDTH = 32;
	const int CHA_HEIGHT = 32;

	enum ENEMYMODE {
		RANDOM,
		RIGHT_HAND,
		LEFT_HAND,

		BFS,
		DFS,

		DIJKSTRA,

		ASTAR,

		MAX_ENEMYMODE
	};