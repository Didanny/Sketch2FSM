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

void ArrowClassifier::initArrows(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector)
{
	for (int i = 0; i < m_arrows.size(); i++)
	{
		std::vector<cv::Point2f> corners = t_image_processor.getFeatures(t_image_processor.componentImage(m_arrows.at(i), t_component_detector.getLabeledImage()));
		Arrow arrow(corners, m_arrows.at(i));
		arrow.initArrow();
		m_arrows_i.push_back(arrow);
	}
}

void ArrowClassifier::initArrowLabels(Components & t_chars)
{
	Component* min_component = NULL;
	//for (int i = 0; i < t_chars.size(); i++)
	//{
	//	cv::Point2f char_center = t_chars.at(i).getCentroid();
	//	for (int j = 0; j < m_arrows.size(); i++)
	//	{
	//		cv::Point2f arrow_center = m_arrows.at(j).getCentroid();
	//		double dist = distance(arrow_center, char_center);
	//		if (dist < min)
	//		{
	//			min = dist;
	//			min_component = &m_arrows.at(j);
	//		}
	//	}
	//}

	for (int i = 0; i < m_arrows.size(); i++)
	{
		double min = 999999999;
		cv::Point2f arrow_center = m_arrows.at(i).getCentroid();
		for (int j = 0; j < t_chars.size(); j++)
		{
			cv::Point2f char_center = t_chars.at(j).getCentroid();
			double dist = distance(arrow_center, char_center);
			if (dist < min)
			{
				min = dist;
				min_component = &t_chars.at(j);
			}
		}
		if (min_component != NULL) m_arrows_i.at(i).addLabel(*min_component);
	}
}

std::vector<int> ArrowClassifier::getLabelLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_arrows_i.size(); i++)
	{
		for (int j = 0; j < m_arrows_i.at(i).m_labels.size(); j++)
		{
			int label = m_arrows_i.at(i).m_labels.at(j).getLabel();
			labels.push_back(label);
		}
	}
	return labels;
}

void ArrowClassifier::initPaths(std::vector<State>& t_states)
{
	for (int i = 0; i < m_arrows_i.size(); i++)
	{
		m_arrows_i.at(i).initPath(t_states);
	}
}
