#include "ComponentsWithStats.h"

ComponentsWithStats::ComponentsWithStats()
{}

ComponentsWithStats::~ComponentsWithStats()
{}

int ComponentsWithStats::getMeanArea()
{
	int sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getArea();
	}
	return (sum / this->size());
}

int ComponentsWithStats::getMeanBoxArea()
{
	int sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getBoundingBox().area;
	}
	return (sum / this->size());
}

double ComponentsWithStats::getVariance(Stat t_stat)
{
	return 0.0;
}

double ComponentsWithStats::getStdev(Stat t_stat)
{
	return 0.0;
}