#include "Component.h"

// Constructor
Component::Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy, int t_label)
	: m_area(t_area), m_container(NULL), m_label(t_label)
{
	m_bounding_box = cv::Rect(t_x, t_y, t_width, t_height);
	m_centroid = cv::Point(t_cx, t_cy);
}

// Destructor
Component::~Component()
{}

cv::Rect Component::getBoundingBox()
{
	return m_bounding_box;
}

int Component::getArea()
{
	return m_area;
}

bool Component::contains(Component& t_component)
{
	int my_left = getBoundingBox().x;
	int my_right = my_left + getBoundingBox().width;
	int my_top = getBoundingBox().y;
	int my_bottom = my_top + getBoundingBox().height;

	int their_left = t_component.getBoundingBox().x;
	int their_right = their_left + t_component.getBoundingBox().width;
	int their_top = t_component.getBoundingBox().y;
	int their_bottom = their_top + t_component.getBoundingBox().height;

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
	return Component(getBoundingBox().x, getBoundingBox().y, getBoundingBox().width, getBoundingBox().height, getBoundingBox().area(), getCentroid().x, getCentroid().y, getLabel());
}

int Component::getLabel()
{
	return m_label;
}

bool Component::equals(Component t_component)
{
	return m_label == t_component.getLabel();
}

bool Component::operator<(Component & t_right)
{
	return getLabel() < t_right.getLabel();
}

bool operator==(Component t_left, Component t_right)
{
	return t_left.getLabel() == t_right.getLabel();
}

bool operator<(Component t_left, Component t_right)
{
	return t_left.getLabel() < t_right.getLabel();
}
