#pragma once

#include <math.h>
template<typename T>
inline double dotProduct(T& l, T& r)
{
	return l*r;
}

template<typename T, unsigned int N>
inline double powerDot(T& l, T& r)
{
	double dot = dotProduct<T>(l,r);
	double ret = 1;
	for (size_t i = 0; i < N; i++)
	{
		ret *= (dot + 1);
	}
	return ret;
}
const double sigma = 0.77;
template<typename T>
inline double gaussDot(T& l, T& r)
{
	//std::cout << exp(-((l - r)*(l - r)) / sigma) << std::endl;
	return exp(-((l - r)*(l - r)) / sigma);
}

const double kappa = 0.12;
const double delta = 0.3;
template<typename T>
inline double tanhDot(T& l, T& r)
{
	return tanh(kappa*(l*r) - delta);
}