#pragma once

#include "Container.h"

typedef std::vector<Container> Containers;

class CircleClassifier 
{
private:
	Containers m_containers;
public:
	CircleClassifier(); // Constructor
	~CircleClassifier(); // Destructor
	void initContainers(); // initializes the containers
	bool isCircle(Container t_container); // returns true if the container is in fact a circle
};