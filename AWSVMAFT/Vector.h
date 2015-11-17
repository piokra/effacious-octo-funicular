#pragma once
#include <memory>
struct Vector
{
public:
	Vector(int size);
	Vector(int size, double* data);
	

	double* values;
	int size;
	
	double length();
	double lengthSquared();

	friend Vector operator + (const Vector& l, const Vector& r);
	friend Vector operator - (const Vector& l, const Vector& r);
	friend double operator * (const Vector& l, const Vector& r);
	friend Vector operator * (const double& l, const Vector& r);
	friend Vector operator * (const Vector& l, const double& r);
private:
	std::shared_ptr<double> hiddenPointer;
};

