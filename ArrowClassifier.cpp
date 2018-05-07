#include "ArrowClassifier.h"

// Constructor
ArrowClassifier::ArrowClassifier(Components & t_components, std::vector<int> t_labels)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		if (!(t_components.at(i).m_label == t_labels))
		{
			m_arrows.push_back(t_components.at(i));
		}
	}
}

// Destructor
ArrowClassifier::~ArrowClassifier()
{}

// Returns vector of labels of the arrows 
std::vector<int> ArrowClassifier::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_arrows_i.size(); i++)
	{
		labels.push_back(m_arrows_i.at(i).m_arrow.m_label);
	}
	return labels;
}

// Initialize the m_arrows_i vector
void ArrowClassifier::initArrows(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector)
{
	for (int i = 0; i < m_arrows.size(); i++)
	{
		std::vector<cv::Point2f> corners = t_image_processor.getFeatures(t_image_processor.componentImage(m_arrows.at(i), t_component_detector.m_labeled_image));
		Arrow arrow(corners, m_arrows.at(i));
		// Find the start and end of the arrow
		arrow.initArrow();
		m_arrows_i.push_back(arrow);
	}
}

// Finds the closest arrow to each character and links them
void ArrowClassifier::initArrowLabels(Components & t_chars)
{
	Component* min_component = NULL;
	// Iterate over all characters
	for (int i = 0; i < t_chars.size(); i++)
	{
		// Find the arrow closest to each
		double min = 999999999;
		cv::Point2f char_center = t_chars.at(i).m_centroid;
		Arrow* arrow_to_add = NULL;
		for (int j = 0; j < m_arrows.size(); j++)
		{
			cv::Point2f arrow_center = m_arrows.at(j).m_centroid;
			double dist = distance(arrow_center, char_center);
			if (dist < min)
			{
				min = dist;
				arrow_to_add = &m_arrows_i.at(j);
			}
		}
		// Add the character to the arrow's label vector
		if (arrow_to_add) arrow_to_add->addLabel(t_chars.at(i));
	}
}

// Returns vector of labels of the arrow characters
std::vector<int> ArrowClassifier::getLabelLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_arrows_i.size(); i++)
	{
		for (int j = 0; j < m_arrows_i.at(i).m_labels.size(); j++)
		{
			int label = m_arrows_i.at(i).m_labels.at(j).m_label;
			labels.push_back(label);
		}
	}
	return labels;
}

// Initializes the states of each arrow
void ArrowClassifier::initPaths(std::vector<State>& t_states)
{
	for (int i = 0; i < m_arrows_i.size(); i++)
	{
		m_arrows_i.at(i).initPath(t_states);
	}
}
