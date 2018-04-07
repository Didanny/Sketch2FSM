#include "Container.h"

Container::Container(Component& t_container)
	: m_container(&t_container)
{}

Container::Container(Component& t_container, Component t_child)
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

void Container::addChild(Component t_child)
{
	getChildren().push_back(t_child);
}

bool Container::isCircle()
{
	return false;
}
