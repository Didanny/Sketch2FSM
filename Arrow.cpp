#include "Arrow.h"

// Constructor
Arrow::Arrow(std::vector<cv::Point2f> t_corners, Component& t_arrow)
	: m_corners(t_corners), m_arrow(t_arrow)
{
	for (int i = 0; i < m_corners.size(); i++)
	{
		m_visited.push_back(false);
	}
	m_visited.at(0) = true;
}

// Destructor
Arrow::~Arrow()
{}

// Gets the nearest unvisited point, from the current point
int Arrow::getNearestPoint(cv::Point2f t_point)
{
	cv::Point2f current_point = t_point;
	cv::Point2f nearest_point;
	float min_distance = 99999999;
	int nearest_index = -1;
	// Find the nearest unvisitec corner
	for (int i = 0; i < m_corners.size(); i++)
	{
		if (m_visited.at(i)) continue;

		cv::Point2f next_point = m_corners.at(i);
		float current_distance = sqrt(pow((current_point.x - next_point.x), 2) + pow((current_point.y - next_point.y), 2));

		if (current_distance < min_distance)
		{
			nearest_index = i;
			min_distance = current_distance;
		}
	}
	return nearest_index;
}

// Initialize the start and end of the arrow
void Arrow::initArrow()
{
	// Given the corners of the arrow connect the dots to find the skeleton of the arrow
	// while recording the slopes of the lines made. Points where the slope changes a lot
	// are candidates for the head, according to this the start is determines afterwards
	if (m_corners.size() < 3)
	{
		m_start = m_end = m_corners.at(0);
		return;
	}
	cv::Point2f current_point = m_corners.at(0);
	cv::Point2f next_point;
	int next_index = getNearestPoint(current_point);
	double previous_slope;
	double current_slope;
	previous_slope = 0;
	bool first = true;
	std::vector<cv::Point2f> ends;
	//std::cout << "RATIOS:\n";
	double max_angle = 0;
	std::stack<cv::Point2f> end_stack;
	int end_index = 0;
	while (next_index < m_corners.size() && next_index > -1)
	{
		next_point = m_corners.at(next_index);
		m_visited.at(next_index) = true;

		current_slope = (next_point.y - current_point.y) / (next_point.x - current_point.x);
		current_point = next_point;
		next_index = getNearestPoint(current_point);

		double angle;
		if (!first)
		{
			// Calcuate angle between current line and previous line
			angle = abs(atan((current_slope - previous_slope) / (1 + (current_slope * previous_slope))));
			// Find the points where the slope changes a long and push them to a stack
			if (angle > max_angle)
			{
				end_stack.push(current_point);
			}
		}
		first = false;
		previous_slope = current_slope;
		end_index++;
	}
	float sum_x = 0;
	float sum_y = 0;

	// Average out the points where the slope changes a lot, this will be the head
	for (int i = 0; i < 3; i++)
	{
		sum_x += end_stack.top().x;
		sum_y += end_stack.top().y;
		end_stack.pop();
	}
	cv::Point2f end(sum_x / 3, sum_y / 3);
	m_end = end;
	cv::Point2f s1 = m_corners.at(0);
	cv::Point2f s2 = m_corners.at(end_index);

	// Decide whether to keep the start unchanged or move it to the other side if it is
	// too close to the head
	float d1 = sqrt(pow((s1.x - end.x), 2) + pow((s1.y - end.y), 2));
	float d2 = sqrt(pow((s2.x - end.x), 2) + pow((s2.y - end.y), 2));
	if (d1 > d2)
	{
		m_start = s1;
	}
	else
	{
		m_start = s2;
	}


	float shift_x = m_arrow.m_bounding_box.x;
	float shift_y = m_arrow.m_bounding_box.y;
	
	// Shift the points by the bounding box coords so they correspond to absolute positions
	// in the original image
	m_start.x += shift_x;
	m_start.y += shift_y;
	m_end.x += shift_x;
	m_end.y += shift_y;
	return;
}

// Adds a character to the m_labels vector
void Arrow::addLabel(Component & t_label)
{
	m_labels.push_back(t_label);
}

// Initializes the state pointers
void Arrow::initPath(std::vector<State>& t_states)
{
	// Find the nearest state to the start point and the end point and set
	// the state pointers accordingly
	double min_start_dist = std::numeric_limits<double>::max();
	double min_end_dist = std::numeric_limits<double>::max();
	for (int j = 0; j < t_states.size(); j++)
	{
		cv::Point2f state_center = t_states.at(j).m_circle.m_centroid;

		double dist_start = distance(state_center, m_start) - t_states.at(j).getRadius();
		double dist_end = distance(state_center, m_end) - t_states.at(j).getRadius();

		if (dist_start < min_start_dist)
		{
			min_start_dist = dist_start;
			m_source = &t_states.at(j);
		}
		if (dist_end < min_end_dist)
		{
			min_end_dist = dist_end;
			m_destination = &t_states.at(j);
		}
	}
}

// Returns a vector of the compinent labels of the arrow labels
std::vector<int> Arrow::getLabelLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_labels.size(); i++)
	{
		labels.push_back(m_labels.at(i).m_label);
	}
	return labels;
}

// Euclidean distance between 2 points
double distance(cv::Point2f & t_first, cv::Point2f & t_second)
{
	return sqrt(pow((t_first.x - t_second.x), 2) + pow((t_first.y - t_second.y), 2));;
}