#pragma once
//All number-related function are stored here

template <typename T>
void clamp( T &value, T valuemin, T valuemax)
{
	if (value > valuemax) {
		value = valuemax;
	}
	else
	{
		if (value < valuemin) {
			value = valuemin;
		}
	}
}