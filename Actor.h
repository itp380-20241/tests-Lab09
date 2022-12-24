#pragma once
#include "Math.h"

class Actor
{
public:
	Actor(const Vector3& pos, float scale)
	: mPosition(pos)
	, mScale(scale)
	{
	}

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetScale() const { return mScale; }

private:
	Vector3 mPosition;
	Vector3 mScale;
};
