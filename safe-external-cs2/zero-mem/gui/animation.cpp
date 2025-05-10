#include "animation.h"

void Animation::AnimateFadeInFadeOut() {
	if (this->Tick) { // fading out
		this->Alpha -= this->Speed;
		if (this->Alpha <= 0.0f) {
			this->Alpha = 0.0f;
			this->Tick = false; // start fading in
		}
	}
	else { // fading in
		this->Alpha += this->Speed;
		if (this->Alpha >= limit) {
			this->Alpha = limit;
			this->Tick = true; // start fading out
		}
	}
}