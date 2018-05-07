#include "CircleClassifier.h"
#include <iostream>

// Returns index of container if found, -1 if not
int Containers::indexOf(Container t_container)
{
	int label = t_container.m_container->m_label;
	for (int i = 0; i < this->size(); i++)
	{
		if (this->at(i).m_container->m_label == label)
		{
			return i;
		}
	}
	return -1;
}

// Constructor
CircleClassifier::CircleClassifier(cv::Mat t_labeled_image)
	: m_labeled_image(t_labeled_image)
{}

// Destructor
CircleClassifier::~CircleClassifier()
{}

// Populates the m_containers vector
void CircleClassifier::initContainers(Components& t_components)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		//std::cout << "i=" << i << " size=" << t_components.size() << std::endl;
		if (t_components.at(i).m_is_container)
		{
			m_containers.push_back(t_components.at(i));
			std::cout << "new=" << t_components.at(i).m_label << std::endl;
		}
	}
	initChildren(t_components);
}

// Populates the children vector of each containers
void CircleClassifier::initChildren(Components& t_components)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		if (t_components.at(i).m_container != NULL)
		{
			//std::cout << "my_container=" << t_components.at(i).m_container->m_label;
			for (int j = 0; j < m_containers.size(); j++)
			{
				//std::cout << "---container=" << m_containers.at(j).m_container->m_label << std::endl;
				if (m_containers.at(j).m_container->m_label == t_components.at(i).m_container->m_label)
				{
					m_containers.at(j).addChild(t_components.at(i));
				}
			}
		}
	}
}

// Returns true if the container is a circle
bool CircleClassifier::isCircle(Container t_container, std::vector<cv::Vec4i>& t_hierarchy)
{
	// Checks the contour hierarchy of the container and its children, if there are
	// no parent-child relatioships return false, else return true
	for (int i = 0; i < t_hierarchy.size(); i++)
	{
		if (t_hierarchy.at(i)[2] != -1)
		{
			return true;
		}
	}
	return false;
}

// Finds the circles among the containers, and returns a vector of them
Containers CircleClassifier::findCircles(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector)
{
	Containers circles;
	for (int i = 0; i < m_containers.size(); i++)
	{
		std::vector<cv::Vec4i> hierarchy = t_image_processor.getHierarchy(m_containers.at(i), t_component_detector.m_labeled_image);
		if (isCircle(m_containers.at(i), hierarchy))
		{
			circles.push_back(m_containers.at(i));
		}
	}
	return circles;
}

// Displays the labels fo the containers
void CircleClassifier::displayContainerLabels()
{
	for (int i = 0; i < m_containers.size(); i++)
	{
		Component c = *m_containers.at(i).m_container;
		std::cout << c.m_label << std::endl;
	}
}
