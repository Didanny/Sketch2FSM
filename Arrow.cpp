#include "Arrow.h"

Arrow::Arrow(cv::Point2f t_start, cv::Point2f t_end) 
	: m_start(t_start), m_end(t_end)
{
}

Arrow::Arrow(std::vector<cv::Point2f> t_corners)
	: m_corners(t_corners)
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
}
