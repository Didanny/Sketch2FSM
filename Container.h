#pragma once

#include "ComponentDetector.h"

class Container
{
private:
	Component* m_container;
	Components m_children;
public:
	Container(Component& t_container); // Constructor
	Container(Component& t_container, Component t_child); // Constructor with first child
	~Container(); // Desctructor
	Components getChildren(); // Returns m_children
	void addChild(Component t_child); // Adds child to m_children
};