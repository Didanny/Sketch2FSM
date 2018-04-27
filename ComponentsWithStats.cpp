#include "ComponentsWithStats.h"

ComponentsWithStats::ComponentsWithStats()
{}

ComponentsWithStats::~ComponentsWithStats()
{}

int ComponentsWithStats::indexOf(Component t_component)
{
	int label = t_component.getLabel();
	for (int i = 0; i < size(); i++)
	{
		if (label == at(i).getLabel())
		{
			return i;
		}
	}
	return -1;
}

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

double ComponentsWithStats::getMeanHeight()
{
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getBoundingBox().height;
	}
	return (sum / this->size());
}

double ComponentsWithStats::getMeanWidth()
{
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += this->at(i).getBoundingBox().width;
	}
	return (sum / this->size());
}

double ComponentsWithStats::getVarianceHeight()
{
	double mean = getMeanHeight();
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += pow((this->at(i).getBoundingBox().height - mean), 2.0);
	}
	return sum / this->size() - 1;
}

double ComponentsWithStats::getVarianceWidth()
{
	double mean = getMeanWidth();
	double sum = 0;
	for (int i = 0; i < this->size(); i++)
	{
		sum += pow((this->at(i).getBoundingBox().width - mean), 2.0);
	}
	return sum / this->size() - 1;
}

double ComponentsWithStats::getStdevHeight()
{
	return sqrt(getVarianceHeight());
}

double ComponentsWithStats::getStdevWidth()
{
	return sqrt(getVarianceWidth());
}

void ComponentsWithStats::findChars(Components& t_components)
{
	int tolerance = 6;
	double min_width = getMeanWidth() - tolerance * getStdevWidth();
	double max_width = getMeanWidth() + tolerance * getStdevWidth();
	double min_height = getMeanHeight() - tolerance * getStdevHeight();
	double max_height = getMeanHeight() + tolerance * getStdevHeight();
	for (int i = 0; i < t_components.size(); i++)
	{
		int height = t_components.at(i).getBoundingBox().height;
		int width = t_components.at(i).getBoundingBox().width;
		if (indexOf(t_components.at(i)) == -1 &&
			width >= min_width && width <= max_width &&
			height >= min_height && height <= max_height)
		{
			t_components.at(i).setClassified();
			push_back(t_components.at(i));
		}
	}
}
