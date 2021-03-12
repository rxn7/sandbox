#pragma once

#include "Libs.h"
#include "glm/gtc/noise.hpp"

namespace Math {
	float sumOctave(uint8_t numIterations, int x, int z, float persistence, float scale, float low, float high) {
		float maxAmp = 0;
		float amp = 1;
		float freq = scale;
		float noise = 0;

		for (int i = 0; i<numIterations; i++) {
			noise += glm::simplex(glm::vec2(x * freq, z * freq)) * amp;
			maxAmp += amp;
			amp *= persistence;
			freq *= 2;
		}
		noise /= maxAmp;

		noise = noise * (high - low) / 2 + (high + low) / 2;

		return noise;
	}
}