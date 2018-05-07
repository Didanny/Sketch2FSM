#include "CharacterClassifier.h"

// Constructor
CharacterClassifier::CharacterClassifier()
{}

// Destructor
CharacterClassifier::~CharacterClassifier()
{}

// Returns index of t_component if found, -1 if not
int CharacterClassifier::indexOf(Component t_component)
{
	int label = t_component.m_label;
	for (int i = 0; i < m_chars.size(); i++)
	{
		if (label == m_chars.at(i).m_label)
		{
			return i;
		}
	}
	return -1;
}

// Returns mean of heights
double CharacterClassifier::getMeanHeight()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).m_bounding_box.height;
	}
	return (sum / m_chars.size());
}

// Returns mean of widths
double CharacterClassifier::getMeanWidth()
{
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += m_chars.at(i).m_bounding_box.width;
	}
	return (sum / m_chars.size());
}

// Returns variance of heights
double CharacterClassifier::getVarianceHeight()
{
	double mean = getMeanHeight();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).m_bounding_box.height - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

// Returns variance of widths
double CharacterClassifier::getVarianceWidth()
{
	double mean = getMeanWidth();
	double sum = 0;
	for (int i = 0; i < m_chars.size(); i++)
	{
		sum += pow((m_chars.at(i).m_bounding_box.width - mean), 2.0);
	}
	return sum / m_chars.size() - 1;
}

// Return standard deviation of heights
double CharacterClassifier::getStdevHeight()
{
	return sqrt(getVarianceHeight());
}

// Returns standard deviation of widths
double CharacterClassifier::getStdevWidth()
{
	return sqrt(getVarianceWidth());
}

// Finds remaining characters in image
void CharacterClassifier::findChars(Components& t_components)
{
	// The assumption here is that the characters are all of similar font size
	int tolerance = 6;
	double min_width = getMeanWidth() - tolerance * getStdevWidth();
	double max_width = getMeanWidth() + tolerance * getStdevWidth();
	double min_height = getMeanHeight() - tolerance * getStdevHeight();
	double max_height = getMeanHeight() + tolerance * getStdevHeight();
	for (int i = 0; i < t_components.size(); i++)
	{
		int height = t_components.at(i).m_bounding_box.height;
		int width = t_components.at(i).m_bounding_box.width;
		if (indexOf(t_components.at(i)) == -1 &&
			width >= min_width && width <= max_width &&
			height >= min_height && height <= max_height)
		{
			m_chars.push_back(t_components.at(i));
			m_chars_unclassified.push_back(t_components.at(i));
		}
	}
}

// Retusn vector of labels of the character components
std::vector<int> CharacterClassifier::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_chars.size(); i++)
	{
		labels.push_back(m_chars.at(i).m_label);
	}
	return labels;
}
