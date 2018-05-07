#include "State.h"
#include <iostream>

State::State(Component t_component, std::string t_name)
	: m_circle(t_component), m_name(t_name), m_is_accept(false)
{
	std::cout << "STATE" << t_component.m_label << m_circle.m_label << "\n";
}

State::~State()
{
}

void State::setAccept()
{
	m_is_accept = true;
}

double State::getRadius()
{
	if (m_is_accept) return 1.2 * ((m_circle.m_bounding_box.width + m_circle.m_bounding_box.y) / 4.0);
	return (m_circle.m_bounding_box.width + m_circle.m_bounding_box.y) / 4.0;
}

std::string State::toString()
{
	return "S," + 
		m_name + "," + 
		std::to_string(m_circle.m_label) + "," + 
		std::to_string(m_circle.getCentroid().x) + "," +
		std::to_string(m_circle.getCentroid().y) + "," +
		std::to_string(getRadius()) + "," + 
		std::to_string(m_is_accept) + "\n";
}
