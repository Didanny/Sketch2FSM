#pragma once

#include "ComponentDetector.h"
#include <stack>

class Arrow
{
private:
	//cv::Point2f m_start;
	//cv::Point2f m_end;
public:
	cv::Point2f m_start;
	cv::Point2f start2;
	cv::Point2f m_end;
	Component m_arrow;
	std::vector<Component> m_labels;

	std::vector<cv::Point2f> m_corners;
	std::vector<bool> m_visited;

	Arrow(std::vector<cv::Point2f> t_corners, Component& t_arrow); // Constructor
	~Arrow(); // Destructor
	int getNearestPoint(cv::Point2f t_point);
	void initArrow(); // initializes start and end points
	void addLabel(Component& t_label); // Adds label to m_labels
};

double distance(cv::Point2f& t_first, cv::Point2f& t_second);