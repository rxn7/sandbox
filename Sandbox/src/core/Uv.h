#pragma once

#include <cstdint>

struct UV {
	UV() {
		this->y = 0;
		this->x = 0;
	}

	UV(float x, float y) {
		this->y = y;
		this->x = x;
	}

	float x;
	float y;
};