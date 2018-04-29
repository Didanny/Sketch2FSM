#pragma once

#include "ComponentsWithStats.h"
#include "ImageProcessor.h"

class ArrowClassifier
{
private:
	//Components m_arrows;
public:
	Components m_arrows;
	ArrowClassifier(Components& t_components, std::vector<int> t_labels); // Constructor
	~ArrowClassifier(); // Destructor
	std::vector<int> getLabels();
	cv::Point2f getNearestPoint(cv::Point2f t_point, std::vector<cv::Point2f> t_corners);
};