#pragma once

#include "ComponentDetector.h"

class Container
{
private:

	Components m_children;
public:	
	Component* m_container;
	Container(Component& t_container); // Constructor
	Container(Component& t_container, Component& t_child); // Constructor with first child
	~Container(); // Desctructor
	Components& getChildren(); // Returns m_children
	void addChild(Component& t_child); // Adds child to m_children
	bool isCircle(); // Returns true if container is in fact a circle
	cv::Mat containerImage(); // Returns an image of just the container and the children
	std::vector<int> getChildLabels(); // Returns vector of child labels
};

bool operator== (int t_left, std::vector<int> t_right);

struct less_than_label
{
	inline bool operator() (const Container& struct1, const Container& struct2)
	{
		return (struct1.m_container->m_label < struct2.m_container->m_label);
	}
};

struct equal_label
{
	inline bool operator() (const Container& struct1, const Container& struct2)
	{
		return (struct1.m_container->m_label == struct2.m_container->m_label);
	}
};

