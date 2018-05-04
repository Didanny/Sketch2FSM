#include "Transition.h"

Transition::Transition(State & t_first_state, State & t_next_state, Arrow & t_arrow, std::string t_label)
	: m_first_state(t_first_state), m_next_state(t_next_state), m_arrow(t_arrow), m_label(t_label)
{
}

Transition::~Transition()
{
}

std::string Transition::toString()
{
	if (m_arrow.m_corners.size() < 3) return "";
	return "T," +
		std::to_string(m_first_state.m_circle.getLabel()) + "," +
		std::to_string(m_next_state.m_circle.getLabel()) + "," + 
		m_label + "," +
		std::to_string(m_arrow.m_start.x) + "," +
		std::to_string(m_arrow.m_start.y) + "," + 
		std::to_string(m_arrow.m_end.x) + "," + 
		std::to_string(m_arrow.m_end.y) + "\n";
}
