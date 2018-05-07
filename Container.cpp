#include "Container.h"

// Constructor
Container::Container(Component& t_container)
	: m_container(&t_container)
{}

// Constructor with first child
Container::Container(Component& t_container, Component& t_child)
	: m_container(&t_container)
{
	m_children.push_back(t_child);
}

// Destructor
Container::~Container()
{}

// Add child t_child to m_children vector
void Container::addChild(Component& t_child)
{
	m_children.push_back(t_child);
}

// Return a vector of the labels of the children
std::vector<int> Container::getChildLabels()
{
	std::vector<int> child_labels;
	for (int i = 0; i < m_children.size(); i++)
	{
		child_labels.push_back(m_children.at(i).m_label);
	}
	return child_labels;
}

// Equality operator for vectors of labels
bool operator== (int t_left, std::vector<int> t_right)
{
	bool a = t_left == t_right.at(0);
	for (int i = 1; i < t_right.size(); i++)
	{
		a = a || t_left == t_right.at(i);
	}
	return a;
}