#pragma once
#include "SVM.h"
#include "CoreFunctions.h"
#include "BreastCancerWisconsin.h"
namespace Testing
{
#ifdef TESTING_PRINTING
#include <iostream>
	template<typename T, typename...Args>
	void print(T t, Args...args)
	{
		std::cout << t << " ";
		print(args...);
	}
	template<typename T>
	void print(T t)
	{
		std::cout << t << std::endl;
	}
#endif
#ifndef TESTING_PRINTING
	template<typename...>
	void print(...)
	{

	}
#endif
	void testOne()
	{
		SVM<double> svm(1,1);
		print(svm.testSign(10), svm.testValue(10));
	}
	void testTwo(std::vector<CancerData>& cd)
	{
		//0.357807 0.342729 0.38348 0.330831 0.280754 0.390429 0.328281 0.373845 0.138632
		CancerData v = { 0,0.384316,0.350952,0.381009,0.323521,0.284383,0.37272,0.324327,0.376324,0.112687,0 };
		//v = (1 / v.length())*v;
		double b = -0.545647;
		
			SVM<CancerData, gaussDot<CancerData>> svm(v, b);
			int correct = 0;
			int incorrect = 0;
			int plus = 0;
			int minus = 0;
			for (size_t i = 0; i < cd.size(); i++)
			{

				if (svm.testSign(cd.at(i)) == 1) plus++;
				if (svm.testSign(cd.at(i)) == -1) minus++;
				if (svm.testSign(cd.at(i)) == cd.at(i).type())
					correct++;
				else
					incorrect++;
			}
			print("b ",b," ",correct, " ", incorrect, " plus ", plus, " minus ", minus);
			
		
	}
	template<double(*CoreFunction)(CancerData& l, CancerData& r)>
	void testData(std::vector<CancerData>& cd, SVM<CancerData, CoreFunction> svm)
	{
		int correct = 0;
		int incorrect = 0;
		int falsepositives = 0;
		int falsenegatives = 0;
		double percentileCorrect = 0;
		for (size_t i = 0; i < cd.size(); i++)
		{
			if (svm.testSign(cd.at(i)) == cd.at(i).type()) correct++;
			else
			{
				incorrect++;
				if (svm.testSign(cd.at(i))==-1)
				{
					falsepositives++;
				}
				else
				{
					falsenegatives++;
				}
			}
				

		}
		print("Data size:", cd.size(), "Correctly assigned:", correct, "Incorrectly assigned:", incorrect, "False positives", falsepositives, "False negatives", falsenegatives, "CPercentile:", (double)correct / (double)cd.size(), "C+FPPercentilee",(double(correct+falsepositives)/(double)cd.size()));
	}
}