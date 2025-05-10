#pragma once
#include <sdk/maths/matrix.h>

class CGame
{
public:
	CGame() {}
	~CGame() {}

	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;

	uintptr_t EntityList = 0;
	Matrix4x4 ViewMatrix = {};
};