#pragma once

#include "ComponentDetector.h"
#include <cmath>

typedef enum 
{
	CHAR,
	CIRCLE,
	ARROW
} ComponentType;

typedef enum
{
	BOX, // for the bounding_box stats
	PIX // for the pixel stats
} Stat;

class ComponentsWithStats : public Components
{
private:
	ComponentType m_type; // The type of the components int the 
public:
	ComponentsWithStats(); // Constructor
	~ComponentsWithStats(); // Destructor
	int indexOf(Component t_component); // Returns index of component if found, -1 if not
	double getMeanArea(); // Returns the mean of the areas of the components
	double getMeanBoxArea(); // Returns the mean of the areas of the bounding boxes of the components
	double getVarianceArea(); // Returns variance of Pixel Areas
	double getVarianceBoxArea(); // Returns variance of Box Areas
	double getStdev(Stat t_stat); // Returns the standard deviation of the desired Stat
	double getMeanHeight(); // Returns the mean of the heights of the components
	double getMeanWidth(); // Returns the mean of the width
	double getVarianceHeight(); // Returns the variance of the height
	double getVarianceWidth(); // Returns the variance of the width
	double getStdevHeight(); // Returns the standard deviation of the height
	double getStdevWidth(); // Returns the standard deviation of the width
	void findChars(Components& t_components);
	std::vector<int> getLabels(); // Returns vector of labels
};

//std::vector<int> operator+ (std::vector<int> left, std::vector<int> right)
//{
//	left.insert(left.end(), right.begin(), right.end());
//	return left;
//}