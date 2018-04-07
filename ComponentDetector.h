#pragma once

#include "Component.h"
#include <vector>

typedef std::vector<Component> Components;

class ComponentDetector 
{
public:
	Components m_components; // vector of detected components with populated stats
	cv::Mat m_original_image; // The original binary image used to find components
	cv::Mat m_labeled_image; // Labeled image after connectedComponentsWithStats
public:
	ComponentDetector(cv::Mat t_image); // Constructor
	~ComponentDetector(); // Destructor
	void detectComponents(); // Finds the components and populates the members
	Components& getComponents(); // Returns reference to getComponents
	void findContainers(); // Sets the container for each component
	cv::Mat getLabeledImage(); // Returns the labeled image
};