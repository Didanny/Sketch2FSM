#include "Arrow.h"

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
	return;
}

void Arrow::addLabel(Component & t_label)
{
	m_labels.push_back(t_label);
}

void Arrow::initPath(std::vector<State>& t_states)
{
	double min_start_dist = 9999999;
	double min_end_dist = 9999999;
	for (int i = 0; i < t_states.size(); i++)
	{
		cv::Point2f state_center = t_states.at(i).m_circle.getCentroid();
		double dist_start = distance(state_center, m_start);
		double dist_end = distance(state_center, m_end);
		if (dist_start < min_start_dist)
		{
			min_start_dist = dist_start;
			m_source = &t_states.at(i);
		}
		if (dist_end < min_end_dist)
		{
			min_end_dist = dist_end;
			m_destination = &t_states.at(i);
		}
	}
}

std::vector<int> Arrow::getLabelLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_labels.size(); i++)
	{
		labels.push_back(m_labels.at(i).getLabel());
	}
	return labels;
}

double distance(cv::Point2f & t_first, cv::Point2f & t_second)
{
	return sqrt(pow((t_first.x - t_second.x), 2) + pow((t_first.y - t_second.y), 2));;
}
