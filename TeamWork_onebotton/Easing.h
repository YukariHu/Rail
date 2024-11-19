#pragma once

namespace Easing {
	inline float Linear(float t) {
		return t;
	}

	inline float EaseIn(float t) {
		return t * t;
	}

	inline float EaseOut(float t) {
		return t * (2 - t);
	}
	inline float EaseInOut(float t) {
		return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
	}
}
