#pragma once

#include "ComponentsWithStats.h"
#include "ImageProcessor.h"
#include "Arrow.h"

class ArrowClassifier
{
private:
	//Components m_arrows;
public:
	Components m_arrows;
	std::vector<Arrow> m_arrows_i;

	ArrowClassifier(Components& t_components, std::vector<int> t_labels); // Constructor
	~ArrowClassifier(); // Destructor
	std::vector<int> getLabels();
	cv::Point2f getNearestPoint(cv::Point2f t_point, std::vector<cv::Point2f> t_corners);
	void initArrows(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector); // Finds start and end of each arrow
	void initArrowLabels(Components& t_chars);
	std::vector<int> getArrowLabels();
	std::vector<int> getLabelLabels();
	void initPaths(std::vector<State>& t_states); // Initializes paths of arrows
};