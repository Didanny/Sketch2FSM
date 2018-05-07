#include "State.h"
#include <iostream>

// Constructor
State::State(Component& t_component, std::string t_name)
	: m_circle(t_component), m_name(t_name), m_is_accept(false)
{
	std::cout << "STATE" << t_component.m_label << m_circle.m_label << "\n";
}

// Destructor
State::~State()
{}

// Sets state as accept state
void State::setAccept()
{
	m_is_accept = true;
}

// Returns radius of circle
double State::getRadius()
{
	if (m_is_accept) return 1.1 * ((m_circle.m_bounding_box.width + m_circle.m_bounding_box.y) / 4.0);
	return (m_circle.m_bounding_box.width + m_circle.m_bounding_box.y) / 4.0;
}

// Converts State to string
std::string State::toString()
{
	return "S," + 
		m_name + "," + 
		std::to_string(m_circle.m_label) + "," + 
		std::to_string(m_circle.m_centroid.x) + "," +
		std::to_string(m_circle.m_centroid.y) + "," +
		std::to_string(getRadius()) + "," + 
		std::to_string(m_is_accept) + "\n";
}
