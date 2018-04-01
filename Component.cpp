#include "Component.h"

// Constructor
Component::Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy)
	: m_area(t_area)
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
