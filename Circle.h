#pragma once

#include "CircleClassifier.h"
#include "ComponentsWithStats.h"

class Circles
{
private:
	Containers m_circles;
	int m_accept_index;
public:
	Circles(Containers t_circles); // Constructor
	~Circles(); // Destructor
	ComponentsWithStats getChars(); // Returns the known chars aka container children
	bool isCircle(Component& t_component); // Returns true if the container is a container
	std::vector<int> getLabels(); // Returns vector of labels of circles
	void initAcceptIndex(); // Finds the accept circle, removes it and sets index to correct circle
};