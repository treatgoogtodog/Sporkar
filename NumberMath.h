#pragma once
//All number-related function are stored here

template <typename T>
void clamp(const T &value, T valuemin, T valuemax)
{
	if (value > valuemax) {
		return valuemax;
	}
	else
	{
		if (value < valuemin) {
			return valuemin;
		}
	}
	return value;
}