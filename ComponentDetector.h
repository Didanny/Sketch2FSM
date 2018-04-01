#pragma once

#include "Component.h"
#include <vector>

typedef std::vector<Component> Components;

class ComponentDetector 
{
private:
	Components m_components; // vector of detected components with populated stats
	cv::Mat m_labeled_image; // Labeled image after connectedComponentsWithStats
public:

};