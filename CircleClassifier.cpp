#include "CircleClassifier.h"
#include <iostream>

CircleClassifier::CircleClassifier(cv::Mat t_labeled_image)
	: m_labeled_image(t_labeled_image)
{}

CircleClassifier::~CircleClassifier()
{
}

void CircleClassifier::initContainers(Components t_components)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		if (t_components.at(i).getContainer() != NULL)
		{
			Container container(*t_components.at(i).getContainer(), t_components.at(i));
			m_containers.push_back(container);
		}
	}
	std::sort(m_containers.begin(), m_containers.end(), less_than_label());
	//std::cout << "After std::sort" << std::endl;
	//for (int i = 0; i < m_containers.size(); i++)
	//{
	//	std::cout << m_containers.at(i).m_container->m_label << std::endl;
	//}
	m_containers.erase(std::unique(m_containers.begin(), m_containers.end(), equal_label()), m_containers.end());
	//std::cout << "After std::unique" << std::endl;
	//for (int i = 0; i < m_containers.size(); i++)
	//{
	//	std::cout << m_containers.at(i).m_container->m_label << std::endl;
	//}
	//std::cout << "Done" << std::endl;
}

bool CircleClassifier::isCircle(Container t_container)
{
	return false;
}

Containers CircleClassifier::getContainers()
{
	return m_containers;
}
