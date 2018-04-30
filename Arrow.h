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
	Components m_arrows;

	std::vector<cv::Point2f> m_corners;
	std::vector<bool> m_visited;
	Arrow(cv::Point2f, cv::Point2f); // Constructor
	Arrow(std::vector<cv::Point2f> t_corners); // Constructor
	~Arrow(); // Destructor
	int getNearestPoint(cv::Point2f t_point);
	void initArrow(); // initializes start and end points
};