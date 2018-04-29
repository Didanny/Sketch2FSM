#include "ArrowClassifier.h"

ArrowClassifier::ArrowClassifier(Components & t_components, std::vector<int> t_labels)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		if (!(t_components.at(i).getLabel() == t_labels))
		{
			m_arrows.push_back(t_components.at(i));
		}
	}
}

ArrowClassifier::~ArrowClassifier()
{
}

std::vector<int> ArrowClassifier::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_arrows.size(); i++)
	{
		labels.push_back(m_arrows.at(i).getLabel());
	}
	return labels;
}

cv::Point2f ArrowClassifier::getNearestPoint(cv::Point2f t_point, std::vector<cv::Point2f> t_corners)
{
	//cv::Point2f nearest_point;
	//float min_distance = 99999999;
	//for (int i = 0; i < corners.size(); i++)
	//{
	//	if (visited.at(i) || current_point == corners.at(i)) continue;

	//	cv::Point2f next_point = corners.at(i);
	//	visited.at(i) = true;
	//	float current_distance = sqrt(pow((current_point.x - next_point.x), 2) + pow((current_point.y - next_point.y), 2));

	//	if (current_distance < min_distance)
	//	{
	//		min_distance = current_distance;
	//		nearest_point = next_point;
	//	}
	//}
	return cv::Point2f();
}
