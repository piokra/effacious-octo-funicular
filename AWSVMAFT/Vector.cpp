#include "Vector.h"
#include <math.h>
Vector::Vector(int size)
{
	values = (double*)malloc(sizeof(double)*size);
	for (size_t i = 0; i < size; i++)
	{
		values[i] = 0;
	}
	this->size = size;
	hiddenPointer = std::shared_ptr<double>(values);
}
Vector::Vector(int size, double * data) 
{
	if (data != 0)
	{
		this->size = size;
		values = data;
		hiddenPointer = std::shared_ptr<double>(values);
	}
	else
	{
		Vector::Vector(size);
	}

}

double Vector::length()
{
	return sqrt(lengthSquared());
}

double Vector::lengthSquared()
{
	double res = 0;
	for (size_t i = 0; i < size; i++)
	{
		res += values[i] * values[i];
	}
	return res;
}
Vector operator + (const Vector& l, const Vector& r)
{
	if (l.size != r.size) throw new std::exception("Vector::operator+ wrong size");
	double* values = (double*)malloc(sizeof(double)*r.size);
	for (size_t i = 0; i < r.size; i++)
	{
		values[i] = l.values[i] + r.values[i];
	}
	return Vector(r.size, values);
}
Vector operator - (const Vector& l, const Vector& r)
{
	if (l.size != r.size) throw new std::exception("Vector::operator- wrong size");
	double* values = (double*)malloc(sizeof(double)*r.size);
	for (size_t i = 0; i < r.size; i++)
	{
		values[i] = l.values[i] - r.values[i];
	}
	return Vector(r.size, values);
}
double operator * (const Vector& l, const Vector& r)
{
	if (l.size != r.size) return nan(0);
	double res = 0;
	for (size_t i = 0; i < l.size; i++)
	{
		res += l.values[i] * r.values[i];
	}
	return res;

}
Vector operator * (const double& l, const Vector& r)
{
	double* values = (double*)malloc(sizeof(double)*r.size);
	for (size_t i = 0; i < r.size; i++)
	{
		values[i] = l*r.values[i];
	}
	return Vector(r.size, values);
}
Vector operator * (const Vector& l, const double& r)
{
	return r*l;
}