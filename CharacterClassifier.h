#pragma once

#include "ComponentDetector.h"
#include <cmath>

struct CharacterClassifier
{
	Components m_chars; // Vector of all characters
	Components m_chars_unclassified; // Vectos of characters later added by findChars

	CharacterClassifier(); // Constructor
	~CharacterClassifier(); // Destructor

	int indexOf(Component t_component); // Returns index of component if found, -1 if not
	double getMeanHeight(); // Returns the mean of the heights of the components
	double getMeanWidth(); // Returns the mean of the width
	double getVarianceHeight(); // Returns the variance of the height
	double getVarianceWidth(); // Returns the variance of the width
	double getStdevHeight(); // Returns the standard deviation of the height
	double getStdevWidth(); // Returns the standard deviation of the width
	void findChars(Components& t_components); // Finds remaining characters in image
	std::vector<int> getLabels(); // Returns vector of labels
};