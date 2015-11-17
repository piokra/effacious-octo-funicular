#pragma once
#include <vector>
#include "Vector.h"
#include "CoreFunctions.h"
#include <random>
#include <iostream>


template<typename T, double(*CoreFunction)(T& l, T& r) = dotProduct<T>>
class GradientSVMOptimizer
{
public:
	GradientSVMOptimizer(std::vector<T>& data, int seed = 0, double initialBounds = 100);
	void doIterations(int iterations = 1000);
	double getB();
	T getVector();
protected:
	void countCoreFunctions();
	double countLaplasian(Vector& arg);
	void doOneIteration();
	void fixBounds(Vector& vec);
	Vector countGradient();
	
private:
	double mB;
	double mLastValue;
	double mLastDifference;
	double mCurrentStep;
	std::uniform_real_distribution<double> mDistribution;
	std::mt19937 mRandomEngine;
	Vector mCurrentlyEvaluated;

	std::vector<T> mData;
	std::vector<std::vector<double>> mCoreFunctions;

	///consts

	const double stepChange = 1.05;
	const double stepFailChange = 0.88;
	
};

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline GradientSVMOptimizer<T, CoreFunction>::GradientSVMOptimizer(std::vector<T>& data, int seed, double initalBounds) : mData(data), mRandomEngine(seed), mDistribution(0, initalBounds), mCurrentlyEvaluated(0), mCurrentStep(0), mLastDifference(0)
{
	mB = 0;
	mCurrentStep = 1;
	countCoreFunctions();
	mCurrentlyEvaluated = Vector(mData.size());
	for (size_t i = 0; i < mData.size(); i++)
	{

		mCurrentlyEvaluated.values[i] = mDistribution(mRandomEngine);
	}
	mLastValue = countLaplasian(mCurrentlyEvaluated);
	int x = 0;
	
}



template<typename T, double(*CoreFunction)(T &l, T &r)>
inline void GradientSVMOptimizer<T, CoreFunction>::doIterations(int iterations)
{
	
	for (size_t i = 0; i < iterations; i++)
	{
		doOneIteration();
		if (!(i % 150)) std::cout << i << std::endl;
	}
	std::cout << "LV " << mLastValue << std::endl;
	std::cout << "LD " << mLastDifference << std::endl;
	std::cout << "CS " << mCurrentStep << std::endl;
	std::cout << "GL " << countGradient().length() << std::endl;
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline void GradientSVMOptimizer<T, CoreFunction>::countCoreFunctions()
{
	
	for (size_t i = 0; i < mData.size(); i++)
	{
		mCoreFunctions.push_back(std::vector<double>());
	}
	size_t length = mData.size();
	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0;  j < length;  j++)
		{
			if (i > j)
				mCoreFunctions[i].push_back(mCoreFunctions[j][i]);
			else
				mCoreFunctions[i].push_back( CoreFunction(mData.at(i), mData.at(j)));
		}
	}
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline double GradientSVMOptimizer<T, CoreFunction>::countLaplasian(Vector& arg)
{
	double res = 0;
	for (size_t i = 0; i < mData.size(); i++)
	{
		res += arg.values[i];
		for (size_t j = 0; j < mData.size(); j++)
		{
			res -= 0.5*arg.values[i] * arg.values[j] * mData[i].type()*mData[j].type()*mCoreFunctions[i][j];
		}
	}
	return res;
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline void GradientSVMOptimizer<T, CoreFunction>::doOneIteration()
{
	int iterations = 0;
	Vector grad = countGradient();
	double temp = -INFINITY;
	while (temp < mLastValue)
	{
		Vector tvec = mCurrentlyEvaluated + mCurrentStep*grad;
		fixBounds(tvec);
		temp = countLaplasian(tvec);
		if (temp > mLastValue)
		{
			double difference = temp - mLastValue;
			mCurrentStep *= stepChange;
			mCurrentStep += 10e-2;
			mLastDifference = difference;
			mLastValue = temp;
			mCurrentlyEvaluated = tvec;
		}
		else
		{
			mCurrentStep *= stepFailChange;
		}
		iterations++;
		if (iterations > 100)
		{
			mLastDifference = 0;
			break;
		}
	}
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline void GradientSVMOptimizer<T, CoreFunction>::fixBounds(Vector& vec)
{
	for (size_t i = 0; i < vec.size; i++)
	{
		if (vec.values[i] < 0) vec.values[i] = 0;
		if (vec.values[i] > 2) vec.values[i] = 2;
	}
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline Vector GradientSVMOptimizer<T, CoreFunction>::countGradient()
{
	double* values = (double*)malloc(sizeof(double)*mData.size());

	for (size_t i = 0; i < mData.size(); i++)
	{
		values[i] = 1;
		for (size_t j = 0; j < mData.size(); j++)
		{
			if (i != j)
				values[i] -= 0.5 * mCurrentlyEvaluated.values[j] * mData[i].type()*mData[j].type()*mCoreFunctions[i][j];
			else
				values[i] -= mCurrentlyEvaluated.values[i]*mCoreFunctions[i][i];
		}
	}
	return Vector(mData.size(), values);
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline double GradientSVMOptimizer<T, CoreFunction>::getB()
{
	int worstWrong = 0;
	int bestCorrect = 0;
	double bestB = 0;
	double worstB = 0;
	if (mB*mB > 10e-6) return mB;

	T v;
	v.clear();
	/*
	for (size_t i = 0; i < mCurrentlyEvaluated.size; i++)
	{
		std::cout << mCurrentlyEvaluated.values[i] << " ";
	}
	std::cout << std::endl;*/
	for (size_t i = 0; i < mCurrentlyEvaluated.size; i++)
	{
		v = v + mData[i].type() * mCurrentlyEvaluated.values[i] * mData[i];
	}
	v = (-1 / v.length()) * v;
	std::cout << v << std::endl;

	for (size_t i = 0; i < mData.size(); i++)
	{
		//std::cout << i << std::endl;
		for (size_t j = 0; j < mData.size(); j++)
		{
			if (mData.at(i).type() != mData.at(j).type())
			{
				double tb = -0.5*(mData.at(i)*v + mData.at(j)*v);
				int currentCorrect = 0;
				int currentIncorrect = 0;
				for (size_t k = 0; k < mData.size(); k++)
				{
					SVM<T, CoreFunction> svm(v, tb);
					if (svm.testSign(mData.at(k)) == mData.at(k).type())
					{
						currentCorrect++;
					}
					else
					{
						currentIncorrect++;
					}

					if (currentCorrect > bestCorrect)
					{
						bestCorrect = currentCorrect;
						bestB = tb;
					}
					if (currentIncorrect > worstWrong)
					{
						worstWrong = currentIncorrect;
						worstB = tb;
					}
				}
			}
		}

	}

	std::cout << "BC " << bestCorrect << " BB " << bestB << " WW " << worstWrong << " WB " << worstB << std::endl;
	mB = bestB;
	return mB;
}

template<typename T, double(*CoreFunction)(T &l, T &r)>
inline T GradientSVMOptimizer<T, CoreFunction>::getVector()
{
	T v;
	v.clear();

	for (size_t i = 0; i < mCurrentlyEvaluated.size; i++)
	{
		v = v + mData[i].type() * mCurrentlyEvaluated.values[i] * mData[i];
	}
	v = (-1 / v.length()) * v;
	return v;
}
