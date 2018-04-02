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
		sum += this->at(i).getBoundingBox().area;
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
	return sqrt(sum / this->size() - 1);
}

double ComponentsWithStats::getVarianceBoxArea()
{
	double mean = getMeanBoxArea();
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += pow((this->at(i).getBoundingBox().area - mean), 2.0);
	}
	return sqrt(sum / this->size() - 1);
}

double ComponentsWithStats::getStdev(Stat t_stat)
{
	return 0.0;
}
