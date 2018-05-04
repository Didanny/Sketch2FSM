#include "CharacterClassifier.h"

CharacterClassifier::CharacterClassifier()
{}

CharacterClassifier::~CharacterClassifier()
{}

int CharacterClassifier::indexOf(Component t_component)
{
	int label = t_component.getLabel();
	for (int i = 0; i < m_chars.size(); i++)
	{
		if (label == m_chars.at(i).getLabel())
		{
			return i;
		}
	}
	return -1;
}

double CharacterClassifier::getMeanArea()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).getArea();
	}
	return (sum / m_chars.size());
}

double CharacterClassifier::getMeanBoxArea()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).getBoundingBox().area();
	}
	return (sum / m_chars.size());
}

double CharacterClassifier::getVarianceArea()
{
	double mean = getMeanArea();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).getArea() - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

double CharacterClassifier::getVarianceBoxArea()
{
	double mean = getMeanBoxArea();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).getBoundingBox().area() - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

double CharacterClassifier::getStdev(Stat t_stat)
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

double CharacterClassifier::getMeanHeight()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).getBoundingBox().height;
	}
	return (sum / m_chars.size());
}

double CharacterClassifier::getMeanWidth()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).getBoundingBox().width;
	}
	return (sum / m_chars.size());
}

double CharacterClassifier::getVarianceHeight()
{
	double mean = getMeanHeight();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).getBoundingBox().height - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

double CharacterClassifier::getVarianceWidth()
{
	double mean = getMeanWidth();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).getBoundingBox().width - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

double CharacterClassifier::getStdevHeight()
{
	return sqrt(getVarianceHeight());
}

double CharacterClassifier::getStdevWidth()
{
	return sqrt(getVarianceWidth());
}

void CharacterClassifier::findChars(Components& t_components)
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
			m_chars.push_back(t_components.at(i));
			m_chars_unclassified.push_back(t_components.at(i));
		}
	}
}

std::vector<int> CharacterClassifier::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_chars.size(); i++)
	{
		labels.push_back(m_chars.at(i).getLabel());
	}
	return labels;
}
