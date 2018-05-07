#pragma once

#include "ComponentDetector.h"
#include "State.h"
#include <stack>

struct Arrow
{
	cv::Point2f m_start; // The starting point of the arrow
	cv::Point2f m_end; // The end point of the arrow
	Component m_arrow; // The component representing the arrow
	std::vector<Component> m_labels; // Vector of characters associated to this arrow

	std::vector<cv::Point2f> m_corners; // Vector of corners, produced by cv::goodFeaturesToTrack
	std::vector<bool> m_visited; // Vector of visited corners, used by getNearestPoint

	State* m_source; // Pointer to the source state
	State* m_destination; // Pointer to the destination state

	Arrow(std::vector<cv::Point2f> t_corners, Component& t_arrow); // Constructor
	~Arrow(); // Destructor

	int getNearestPoint(cv::Point2f t_point);
	void initArrow(); // initializes start and end points
	void addLabel(Component& t_label); // Adds label to m_labels
	void initPath(std::vector<State>& t_states); // Initializes the source and destination 
	std::vector<int> getLabelLabels(); // Returns a vector of the compinent labels of the arrow labels
};

double distance(cv::Point2f& t_first, cv::Point2f& t_second); // Euclidean distance between 2 points