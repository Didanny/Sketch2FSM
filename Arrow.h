#pragma once

#include "ComponentDetector.h"
#include "State.h"
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

	State* m_source;
	State* m_destination;

	Arrow(std::vector<cv::Point2f> t_corners, Component& t_arrow); // Constructor
	~Arrow(); // Destructor
	int getNearestPoint(cv::Point2f t_point);
	void initArrow(); // initializes start and end points
	void addLabel(Component& t_label); // Adds label to m_labels
	void initPath(std::vector<State>& t_states); // Initializes the source and destination 
	std::vector<int> getLabelLabels();
};

double distance(cv::Point2f& t_first, cv::Point2f& t_second);
double distance_overflow(cv::Point2f & t_first, cv::Point2f & t_second);