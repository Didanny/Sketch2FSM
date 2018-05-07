#include "Component.h"

// Constructor
Component::Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy, int t_label)
	: m_area(t_area), m_container(NULL), m_label(t_label), m_is_container(false)
{
	m_bounding_box = cv::Rect(t_x, t_y, t_width, t_height);
	m_centroid = cv::Point(t_cx, t_cy);
}

// Destructor
Component::~Component()
{}

//cv::Rect Component::m_bounding_box
//{
//	return m_bounding_box;
//}

//int Component::m_area
//{
//	return m_area;
//}

bool Component::contains(Component& t_component)
{
	int my_left = m_bounding_box.x;
	int my_right = my_left + m_bounding_box.width;
	int my_top = m_bounding_box.y;
	int my_bottom = my_top + m_bounding_box.height;

	int their_left = t_component.m_bounding_box.x;
	int their_right = their_left + t_component.m_bounding_box.width;
	int their_top = t_component.m_bounding_box.y;
	int their_bottom = their_top + t_component.m_bounding_box.height;

	return (their_right < my_right && their_left > my_left && their_top > my_top && their_bottom < my_bottom);
}

void Component::setContainer(Component& t_component)
{
	m_container = &t_component;
}

Component * Component::getContainer()
{
	return m_container;
}

cv::Point Component::getCentroid()
{
	return m_centroid;
}

Component Component::copy()
{
	return Component(m_bounding_box.x, m_bounding_box.y, m_bounding_box.width, m_bounding_box.height, m_bounding_box.area(), getCentroid().x, getCentroid().y, m_label);
}


void Component::setAsContainer()
{
	m_is_container = true;
}

bool Component::isContainer()
{
	return m_is_container;
}
