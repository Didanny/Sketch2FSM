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
	Component child = t_container.getChildren().at(0);
	int origin_x = child.getBoundingBox().x;
	int origin_y = child.getBoundingBox().y;
	int parent_label = t_container.m_container->getLabel();

	int i, j;
	i = j = origin_y;

	bool bounded_above = false;
	bool bounded_below = false;

	while (i < m_labeled_image.rows)
	{
		if (parent_label == m_labeled_image.at<int>(origin_y, i)) bounded_below = true;
		i++;
	}
	while (j > 0)
	{
		if (parent_label == m_labeled_image.at<int>(origin_y, j)) bounded_above = true;
		j--;
	}
	
	return bounded_above & bounded_below;
}

Containers CircleClassifier::getContainers()
{
	return m_containers;
}

Containers CircleClassifier::findCircles()
{
	Containers circles;
	for (int i = 0; i < m_containers.size(); i++)
	{
		if (m_containers.at(i).isCircle())
		{
			circles.push_back(m_containers.at(i));
		}
	}
	return circles;
}

void CircleClassifier::showCircles()
{
	cv::Mat circles_image = m_labeled_image == findCircles().at(0).m_container->getLabel();
	for (int i = 1; i < findCircles().size(); i++)
	{
		//circles_image = circles_image | (circles_image == findCircles().at(i).m_container->getLabel());
	}
	cv::namedWindow("Circles", 1);
	cv::imshow("Circles", circles_image);
	cv::waitKey(0);
}
