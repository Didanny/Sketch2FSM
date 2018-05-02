#include "Circle.h"

Circles::Circles(Containers t_circles)
	: m_circles(t_circles)
{
}

Circles::~Circles()
{
}

Containers Circles::getCircles()
{
	return m_circles;
}

CharacterClassifier Circles::getChars()
{
	CharacterClassifier chars;
	for (int i = 0; i < m_circles.size(); i++)
	{
		Components children = m_circles.at(i).getChildren();
		for (int j = 0; j < children.size(); j++) 
		{
			if (isCircle(children.at(j))) continue;
			children.at(j).setClassified();
			chars.m_chars.push_back(children.at(j));
		}
	}
	return chars;
}

bool Circles::isCircle(Component & t_component)
{
	int label = t_component.getLabel();
	for (int i = 0; i < m_circles.size(); i++)
	{
		if (label == m_circles.at(i).m_container->getLabel())
		{
			return true;
		}
	}
	return false;
}

std::vector<int> Circles::getLabels()
{
	std::vector<int> labels;
	for (int i = 0; i < m_circles.size(); i++)
	{
		labels.push_back(m_circles.at(i).m_container->getLabel());
	}
	return labels;
}

void Circles::initAcceptIndex()
{
	for (int i = 0; i < m_circles.size(); i++)
	{
		for (int j = 0; j < m_circles.at(i).getChildren().size(); j++)
		{
			if (isCircle(m_circles.at(i).getChildren().at(j)))
			{
				int child_label = m_circles.at(i).getChildren().at(j).getLabel();
				m_circles.erase(m_circles.begin() + i);
				for (int k = 0; k < m_circles.size(); k++)
				{
					if (child_label == m_circles.at(k).m_container->getLabel())
					{
						m_accept_index = k;
						return;
					}
				}
			}
		}
	}
}


