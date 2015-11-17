#include <iostream>
#define TESTING_PRINTING 0
#include "BasicTests.h"
#include "BreastCancerWisconsin.h"
#include "GradientSVMOptimizer.h"

using namespace Testing;
int main()
{
	
	
	BreastCancerWisconsin bcw;
	auto bcwd = bcw.getData();
	auto xbcdw = bcwd;
	auto ybcdw = decltype(bcwd)();
	for (size_t i = 0; i < 60; i++)
	{
		ybcdw.push_back(bcwd.at(i + bcwd.size() - 61));
	}
	for (size_t i = 0; i < 60; i++)
	{
		xbcdw.pop_back();
	}

	GradientSVMOptimizer<CancerData,gaussDot<CancerData>> gsvmo(xbcdw);
	gsvmo.doIterations(150);
	double xbcdwb = gsvmo.getB();
	CancerData xbcdwv = gsvmo.getVector();
	testData(xbcdw, SVM<CancerData, gaussDot<CancerData>>(xbcdwv, xbcdwb));
	testData(ybcdw, SVM<CancerData, gaussDot < CancerData >> (xbcdwv, xbcdwb));
	std::getchar();
	return 0;
}