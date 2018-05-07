#include "Circle.h"

// Constructor
Circles::Circles(Containers t_circles)
	: m_circles(t_circles)
{
}

// Destructor
Circles::~Circles()
{
}

// Returns vector of the children of the circles
CharacterClassifier Circles::getChars()
{
	CharacterClassifier chars;
	for (int i = 0; i < m_circles.size(); i++)
	{
		Components children = m_circles.at(i).m_children;
		for (int j = 0; j < children.size(); j++) 
		{
			if (isCircle(children.at(j))) continue;
			chars.m_chars.push_back(children.at(j));
		}
	}
	return chars;
}

// Returns true if components is a circle
bool Circles::isCircle(Component & t_component)
{
	int label = t_component.m_label;
	for (int i = 0; i < m_circles.size(); i++)
	{
		if (label == m_circles.at(i).m_container->m_label)
		{
			return true;
		}
	}
	return false;
}

// Returns vector of labels of the circles
std::vector<int> Circles::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_circles.size(); i++)
	{
		labels.push_back(m_circles.at(i).m_container->m_label);
	}
	return labels;
}

// Initializing the accept Index
void Circles::initAcceptIndex()
{
	// Finds the accept circle, ie the big circle around the accept state
	// removes this circle from the m_circles vector and sets the child index
	// as the m_accept_index
	for (int i = 0; i < m_circles.size(); i++)
	{
		for (int j = 0; j < m_circles.at(i).m_children.size(); j++)
		{
			if (isCircle(m_circles.at(i).m_children.at(j)))
			{
				int child_label = m_circles.at(i).m_children.at(j).m_label;
				Component big_circle = *m_circles.at(i).m_container;
				m_circles.erase(m_circles.begin() + i);
				for (int k = 0; k < m_circles.size(); k++)
				{
					if (child_label == m_circles.at(k).m_container->m_label)
					{
						m_accept_index = k;
						//m_circles.at(k).m_container = new Component(big_circle);
						// TODO: Fix The Radius issue
						return;
					}
				}
			}
		}
	}
}


