#pragma once

#include "Container.h"

typedef std::vector<Container> Containers;

class CircleClassifier 
{
private:
	Containers m_containers;
	cv::Mat m_labeled_image;
public:
	CircleClassifier(cv::Mat t_labeled_image); // Constructor
	~CircleClassifier(); // Destructor
	void initContainers(Components t_components); // initializes the containers
	bool isCircle(Container t_container); // returns true if the container is in fact a circle
	Containers getContainers(); // Returns containers
};