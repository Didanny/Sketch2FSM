#pragma once

#include "Component.h"
#include <vector>

typedef std::vector<Component> Components;

struct ComponentDetector 
{
	Components m_components; // vector of detected components with populated stats
	cv::Mat m_original_image; // The original binary image used to find components
	cv::Mat m_labeled_image; // Labeled image after connectedComponentsWithStats

	ComponentDetector(cv::Mat t_image); // Constructor
	~ComponentDetector(); // Destructor

	void detectComponents(); // Finds the components and populates the members
	void findContainers(); // Sets the container for each component
};