#pragma once

#include "ComponentDetector.h"

struct Container
{
	Components m_children; // Vector of child components
	Component* m_container; // Pointer to parent component

	Container(Component& t_container); // Constructor
	Container(Component& t_container, Component& t_child); // Constructor with first child
	~Container(); // Desctructor

	void addChild(Component& t_child); // Adds child to m_children
	std::vector<int> getChildLabels(); // Returns vector of child labels
};

bool operator== (int t_left, std::vector<int> t_right);

