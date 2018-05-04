#include "State.h"
#include <iostream>

State::State(Component t_component, std::string t_name)
	: m_circle(t_component), m_name(t_name), m_is_accept(false)
{
	std::cout << "STATE" << t_component.getLabel() << m_circle.getLabel() << "\n";
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
	if (m_is_accept) return 1.2 * ((m_circle.getBoundingBox().width + m_circle.getBoundingBox().y) / 4.0);
	return (m_circle.getBoundingBox().width + m_circle.getBoundingBox().y) / 4.0;
}

std::string State::toString()
{
	return "S," + 
		m_name + "," + 
		std::to_string(m_circle.getLabel()) + "," + 
		std::to_string(m_circle.getCentroid().x) + "," +
		std::to_string(m_circle.getCentroid().y) + "," +
		std::to_string(getRadius()) + "\n";
}
