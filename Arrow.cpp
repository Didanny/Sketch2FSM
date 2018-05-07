#include "Arrow.h"
#include <iostream>

Arrow::Arrow(std::vector<cv::Point2f> t_corners, Component& t_arrow)
	: m_corners(t_corners), m_arrow(t_arrow)
{
	for (int i = 0; i < m_corners.size(); i++)
	{
		m_visited.push_back(false);
	}
	m_visited.at(0) = true;
}

Arrow::~Arrow()
{
}

int Arrow::getNearestPoint(cv::Point2f t_point)
{
	cv::Point2f current_point = t_point;
	cv::Point2f nearest_point;
	float min_distance = 99999999;
	int nearest_index = -1;
	for (int i = 0; i < m_corners.size(); i++)
	{
		if (m_visited.at(i)) continue;

		cv::Point2f next_point = m_corners.at(i);
		//m_visited.at(i) = true;
		float current_distance = sqrt(pow((current_point.x - next_point.x), 2) + pow((current_point.y - next_point.y), 2));

		if (current_distance < min_distance)
		{
			nearest_index = i;
			min_distance = current_distance;
		}
	}
	//m_visited.at(nearest_index) = true;
	return nearest_index;
}

void Arrow::initArrow()
{
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
		//if (arrow0.m_visited.at(i)) continue;
		next_point = m_corners.at(next_index);
		m_visited.at(next_index) = true;

		current_slope = (next_point.y - current_point.y) / (next_point.x - current_point.x);
		//std::cout << "slope=" << current_slope << "\n";
		//cv::line(arrow_0copy, current_point, next_point, cv::Scalar(0, 255, 0));
		current_point = next_point;
		next_index = getNearestPoint(current_point);

		double angle;
		if (!first)
		{
			angle = abs(atan((current_slope - previous_slope) / (1 + (current_slope * previous_slope))));
			//std::cout << angle << "\n";
			if (angle > max_angle)
			{
				end_stack.push(current_point);
			}
			//if (angle > 1.39 && angle < 1.75)
			//{
			//	ends.push_back(current_point);
			//	circle(arrow_0copy, current_point, r, cv::Scalar(255, 0, 0), -1, 8, 0);
			//}
		}
		first = false;
		previous_slope = current_slope;
		end_index++;
	}
	float sum_x = 0;
	float sum_y = 0;
	for (int i = 0; i < 3; i++)
	{
		//circle(arrow_0copy, end_stack.top(), r, cv::Scalar(255, 0, 0), -1, 8, 0);
		sum_x += end_stack.top().x;
		sum_y += end_stack.top().y;
		end_stack.pop();
	}
	cv::Point2f end(sum_x / 3, sum_y / 3);
	m_end = end;
	cv::Point2f s1 = m_corners.at(0);
	cv::Point2f s2 = m_corners.at(end_index);
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
	m_start.x += shift_x;
	m_start.y += shift_y;
	m_end.x += shift_x;
	m_end.y += shift_y;
	return;
}

void Arrow::addLabel(Component & t_label)
{
	m_labels.push_back(t_label);
}

void Arrow::initPath(std::vector<State>& t_states)
{
	double min_start_dist = std::numeric_limits<double>::max();
	double min_end_dist = std::numeric_limits<double>::max();
	for (int j = 0; j < t_states.size(); j++)
	{
		cv::Point2f state_center = t_states.at(j).m_circle.getCentroid();

		std::cout << state_center << "\n";
		std::cout << "Start=" << m_start << " End=" << m_end << "\n";

		double dist_start = distance(state_center, m_start) - t_states.at(j).getRadius();
		double dist_end = distance(state_center, m_end) - t_states.at(j).getRadius();
		
		//std::cout << "dist_start=" << dist_start << std::endl;
		//std::cout << "dist_end=" << dist_end << std::endl;

		std::cout << "Arrow" << m_arrow.m_label << "\n";
		std::cout << "Distance from " + t_states.at(j).m_name << " " << dist_end << "\n";
		std::cout << "Distance from " + t_states.at(j).m_name << " " << dist_start << "\n\n";

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

std::vector<int> Arrow::getLabelLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_labels.size(); i++)
	{
		labels.push_back(m_labels.at(i).m_label);
	}
	return labels;
}

double distance(cv::Point2f & t_first, cv::Point2f & t_second)
{
	return sqrt(pow((t_first.x - t_second.x), 2) + pow((t_first.y - t_second.y), 2));;
}

double distance_overflow(cv::Point2f & t_first, cv::Point2f & t_second)
{
	return sqrt(pow((t_first.x - t_second.x)/1000000000000.0, 2) + pow((t_first.y - t_second.y)/1000000000000.0, 2));;
}
