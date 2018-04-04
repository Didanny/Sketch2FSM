#include "ComponentsWithStats.h"

ComponentsWithStats::ComponentsWithStats()
{}

ComponentsWithStats::~ComponentsWithStats()
{}

double ComponentsWithStats::getMeanArea()
{
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getArea();
	}
	return (sum / this->size());
}

double ComponentsWithStats::getMeanBoxArea()
{
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getBoundingBox().area();
	}
	return (sum / this->size());
}

double ComponentsWithStats::getVarianceArea()
{
	double mean = getMeanArea();
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += pow((this->at(i).getArea() - mean), 2.0);
	}
	return sum / this->size() - 1;
}

double ComponentsWithStats::getVarianceBoxArea()
{
	double mean = getMeanBoxArea();
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += pow((this->at(i).getBoundingBox().area() - mean), 2.0);
	}
	return sum / this->size() - 1;
}

double ComponentsWithStats::getStdev(Stat t_stat)
{
	if (t_stat == PIX)
	{
		return sqrt(getVarianceArea());
	}
	else if (t_stat == BOX)
	{
		return sqrt(getVarianceBoxArea());
	}
	return -1;
}
