#pragma once

#include "CircleClassifier.h"
#include "CharacterClassifier.h"

struct Circles
{
	Containers m_circles; // Vector of containers representing the circles
	int m_accept_index; // 

	Circles(Containers t_circles); // Constructor
	~Circles(); // Destructor

	CharacterClassifier getChars(); // Returns the known chars (container children)
	bool isCircle(Component& t_component); // Returns true if the container is a container
	std::vector<int> getLabels(); // Returns vector of labels of circles
	void initAcceptIndex(); // Finds the accept circle, removes it and sets index to correct circle
};