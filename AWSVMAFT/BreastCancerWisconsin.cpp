#include "BreastCancerWisconsin.h"
#include <fstream>
#include <iostream>

BreastCancerWisconsin::BreastCancerWisconsin()
{
	try
	{
		readData();
	}
	catch (...)
	{
		std::cout << "Failed to read the file, exiting" << std::endl;
		std::getchar();
		exit(1);
	}
}


BreastCancerWisconsin::~BreastCancerWisconsin()
{
}

void BreastCancerWisconsin::readData(std::string filename) 
{
	std::ifstream file(filename);
	char line[255];
	while (file.getline(line, 255))
	{
		try
		{
			addData(line);
		}
		catch (...)
		{
			std::cout << "Invalid data read, skipping" << std::endl;
		}
	}

	
}

void BreastCancerWisconsin::addData(char * line)
{
	std::vector<std::string> seperatedData;
	char t = line[0];
	int prevPos = 0;
	int curPos = 0;
	while (t != 0)
	{
		curPos++;
		t = line[curPos];
		if (t == ',')
		{
			seperatedData.push_back(std::string(line+prevPos, curPos - prevPos));
			prevPos = curPos + 1;
		}
		
		
	}
	seperatedData.push_back(std::string(line + prevPos, curPos - prevPos));
	std::vector<int> numberData;
	for (size_t i = 0; i < seperatedData.size(); i++)
	{
		try
		{
			numberData.push_back(castString(seperatedData[i]));
		}
		catch (...)
		{
			std::cout << "Failed to cast string" << std::endl;
		}
		
	}
	if(numberData.size()!=11)throw new std::exception("Invalid data size");
	mData.push_back({numberData[0],(UC)numberData[1]/10,(UC)numberData[2]/10,(UC)numberData[3]/10,(UC)numberData[4]/10,(UC)numberData[5]/10,(UC)numberData[6]/10,(UC)numberData[7]/10,(UC)numberData[8]/10,(UC)numberData[9]/10,(char)((numberData[10]-3)*-1)});
	
}

int BreastCancerWisconsin::castString(std::string str)
{
	int res = 0;
	int d = 1;
	for (int i = str.length()-1; i >= 0; i--)
	{
		if ((str[i] < 48) || (str[i]>57)) throw new std::exception("Not a number");
		res += (str[i] - 48)*d;
		d *= 10;
	}
	return res;
}

const std::vector<CancerData>& BreastCancerWisconsin::getData()
{
	return mData;
}

double operator*(const CancerData & l, const CancerData & r)
{
	double res = 0;
	res += l.clumpThickness*r.clumpThickness;
	res += l.uniformityOfCellSize * r.uniformityOfCellSize;
	res += l.uniformityOfCellShape * r.uniformityOfCellShape;
	res += l.marginalAdhesion * r.marginalAdhesion;
	res += l.singleEpithelialCellSize * r.singleEpithelialCellSize;
	res += l.bareNuclei * r.bareNuclei;
	res += l.blandChromatin * r.blandChromatin;
	res += l.normalNucleoli * r.normalNucleoli;
	res += l.mitoses * r.mitoses;
	return res;
}
CancerData operator*(const double& l, const CancerData& r)
{
	return{ -1, l*r.clumpThickness, l*r.uniformityOfCellSize, l*r.uniformityOfCellShape, l*r.marginalAdhesion, l*r.singleEpithelialCellSize, l*r.bareNuclei, l*r.blandChromatin,l*r.normalNucleoli, l*r.mitoses, 0 };
}
CancerData operator+(const CancerData& l, const CancerData& r)
{
	return{ -1, l.clumpThickness + r.clumpThickness, l.uniformityOfCellSize + r.uniformityOfCellSize, l.uniformityOfCellShape + r.uniformityOfCellShape, l.marginalAdhesion + r.marginalAdhesion, l.singleEpithelialCellSize + r.singleEpithelialCellSize, l.bareNuclei + r.bareNuclei, l.blandChromatin + r.blandChromatin,l.normalNucleoli + r.normalNucleoli, l.mitoses + r.mitoses, 0 };
}

CancerData operator-(const CancerData& l, const CancerData& r)
{
	return{ -1, l.clumpThickness - r.clumpThickness, l.uniformityOfCellSize - r.uniformityOfCellSize, l.uniformityOfCellShape - r.uniformityOfCellShape, l.marginalAdhesion - r.marginalAdhesion, l.singleEpithelialCellSize - r.singleEpithelialCellSize, l.bareNuclei - r.bareNuclei, l.blandChromatin - r.blandChromatin,l.normalNucleoli - r.normalNucleoli, l.mitoses - r.mitoses, 0 };
}

std::ostream& operator<<(std::ostream& stream, const CancerData& r)
{
	stream << "Displaying Cancer Data:" << std::endl;
	if (r.id > 0)
	{
		stream << "ID: " << r.id << std::endl;
	}
	else
	{
		stream << "This is not data." << std::endl;
	}

	stream << "Raw data: " << std::endl;
	stream << r.clumpThickness << " " << r.uniformityOfCellSize << " " << r.uniformityOfCellShape << " " << r.marginalAdhesion << " " << r.singleEpithelialCellSize << " " << r.bareNuclei << " " << r.blandChromatin << " " << r.normalNucleoli << " " << r.mitoses << std::endl;

	switch (r.cancerClass)
	{
	case 1:
		stream << "Maligant" << std::endl;
	case -1:
		stream << "Bening" << std::endl;
	default:
		stream << "This is a vector" << std::endl;
	}
	return stream;
}

double CancerData::length()
{
	return sqrt(lengthSquared());

}

double CancerData::lengthSquared()
{
	double res = 0;
	res += clumpThickness*clumpThickness + uniformityOfCellSize*uniformityOfCellSize + uniformityOfCellShape*uniformityOfCellShape + marginalAdhesion*marginalAdhesion + singleEpithelialCellSize*singleEpithelialCellSize + bareNuclei*bareNuclei + blandChromatin*blandChromatin + normalNucleoli*normalNucleoli + mitoses*mitoses;
	return res;
}

double CancerData::type()
{
	return cancerClass;
}

void CancerData::clear()
{
	*this = { 0,0,0,0,0,0,0,0,0,0,0 };
}
