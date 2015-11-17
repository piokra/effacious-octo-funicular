#pragma once

#include "CoreFunctions.h"


template<typename T, double(*CoreFunction)(T& l, T& r) = dotProduct<T>>
class SVM
{
public:

	//using CoreFunction = double(*)(T& l, T& r);
	SVM(T vector, double b);
	~SVM();
	int testSign(T toCheck);
	double testValue(T toCheck);

private:
	//CoreFunction mCoreFunction;
	T mVector;
	double mB;
};

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline SVM<T, CoreFunction>::SVM(T vector, double b) : mVector(vector), mB(b)
{
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline SVM<T, CoreFunction>::~SVM()
{
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline double SVM<T, CoreFunction>::testValue(T toCheck)
{
	return CoreFunction(toCheck, mVector) + mB;
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline int SVM<T, CoreFunction>::testSign(T toCheck)
{
	double res = CoreFunction(toCheck, mVector) + mB;
	if (res > 0) return 1;
	if (res < 0) return -1;
	return 0;
}
