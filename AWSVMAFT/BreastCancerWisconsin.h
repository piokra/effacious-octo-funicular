#pragma once

#include <string>
#include <vector>
/*
	
	7. Attribute Information: (class attribute has been moved to last column)

	#  Attribute                     Domain
	-- -----------------------------------------
	1. Sample code number            id number
	2. Clump Thickness               1 - 10
	3. Uniformity of Cell Size       1 - 10
	4. Uniformity of Cell Shape      1 - 10
	5. Marginal Adhesion             1 - 10
	6. Single Epithelial Cell Size   1 - 10
	7. Bare Nuclei                   1 - 10
	8. Bland Chromatin               1 - 10
	9. Normal Nucleoli               1 - 10
	10. Mitoses                       1 - 10
	11. Class:                        (2 for benign, 4 for malignant)

	More in breast-cancer-wisconsin.names
*/

using UC = double;
struct CancerData
{
	int id;
	UC clumpThickness;
	UC uniformityOfCellSize;
	UC uniformityOfCellShape;
	UC marginalAdhesion;
	UC singleEpithelialCellSize;
	UC bareNuclei;
	UC blandChromatin;
	UC normalNucleoli;
	UC mitoses;
	char cancerClass;

	friend double operator*(const CancerData& l, const CancerData& r);
	friend CancerData operator*(const double& l, const CancerData& r);
	friend CancerData operator+(const CancerData& l, const CancerData& r);
	friend std::ostream& operator<<(std::ostream& stream, const CancerData& r);
	friend CancerData operator-(const CancerData& l, const CancerData& r);
	double length();
	double lengthSquared();
	double type();
	void clear();
};

class BreastCancerWisconsin
{
public:
	BreastCancerWisconsin();
	~BreastCancerWisconsin();

	void readData(std::string filename = "breast-cancer-wisconsin.data");
	void addData(char* line);
	int castString(std::string str);
	const std::vector<CancerData>& getData();
private:
	std::vector<CancerData> mData;
};

