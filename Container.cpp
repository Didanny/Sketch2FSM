#include "Container.h"

Container::Container(Component& t_container)
	: m_container(&t_container)
{}

Container::Container(Component& t_container, Component& t_child)
	: m_container(&t_container)
{
	m_children.push_back(t_child);
}

Container::~Container()
{}

Components Container::getChildren()
{
	return m_children;
}

void Container::addChild(Component& t_child)
{
	m_children.push_back(t_child);
}

bool Container::isCircle()
{
	return false;
}

cv::Mat Container::containerImage()
{
	cv::Mat container_image = cv::Mat();
	return container_image;
}

std::vector<int> Container::getChildLabels()
{
	std::vector<int> child_labels;
	for (int i = 0; i < m_children.size(); i++)
	{
		child_labels.push_back(m_children.at(i).getLabel());
	}
	return child_labels;
}

bool operator== (int t_left, std::vector<int> t_right)
{
	bool a = t_left == t_right.at(0);
	for (int i = 1; i < t_right.size(); i++)
	{
		a = a || t_left == t_right.at(i);
	}
	return a;
}