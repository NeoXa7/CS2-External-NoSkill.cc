#pragma once
#include <globals/imports.h>

struct Animation {
public:
	float limit = 255.0f;
	float Alpha;
	float Speed;
	bool Tick;

	Animation(float Limit, float alpha, float speed, bool tick) : limit(Limit), Alpha(alpha), Speed(speed), Tick(tick) {}

	void AnimateFadeInFadeOut();
};
