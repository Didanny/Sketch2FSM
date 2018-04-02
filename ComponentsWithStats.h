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
	double getMeanArea(); // Returns the mean of the areas of the components
	double getMeanBoxArea(); // Returns the mean of the areas of the bounding boxes of the components
	double getVariance(Stat t_stat); // Returns variance of desired Stat
	double getStdev(Stat t_stat); // Returns the standard deviation of the desired Stat
};