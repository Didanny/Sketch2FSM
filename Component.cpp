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

// Returns true of t_component is contained within the bounding box of this component
bool Component::contains(Component& t_component)
{
	// Getting the sides of this component's bounding box
	int my_left = m_bounding_box.x;
	int my_right = my_left + m_bounding_box.width;
	int my_top = m_bounding_box.y;
	int my_bottom = my_top + m_bounding_box.height;

	// Getting the sides of t_component's bounding box
	int their_left = t_component.m_bounding_box.x;
	int their_right = their_left + t_component.m_bounding_box.width;
	int their_top = t_component.m_bounding_box.y;
	int their_bottom = their_top + t_component.m_bounding_box.height;

	return (their_right < my_right && their_left > my_left && their_top > my_top && their_bottom < my_bottom);
}

// Sets the value of m_container
void Component::setContainer(Component& t_component)
{
	m_container = &t_component;
}

// Returns a copy of this component
Component Component::copy()
{
	return Component(m_bounding_box.x, m_bounding_box.y, m_bounding_box.width, m_bounding_box.height, m_bounding_box.area(), m_centroid.x, m_centroid.y, m_label);
}

// Sets this component as a container
void Component::setAsContainer()
{
	m_is_container = true;
}
