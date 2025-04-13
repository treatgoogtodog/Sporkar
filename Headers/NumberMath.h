#pragma once
//All number-related function are stored here

const double MathPi = 3.1415;

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

template <typename T>
T abs(T value) {
	if (value > 0) { return value; }
	return -value;
}

double sine(const double& a) {
	return a - (a * a * a) / 6 + (a * a * a * a * a) / 120; //MacClaurinXpandsion
}