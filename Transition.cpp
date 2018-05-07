#include "Transition.h"

// Constructor
Transition::Transition(State & t_first_state, State & t_next_state, Arrow & t_arrow, std::string t_label)
	: m_first_state(t_first_state), m_next_state(t_next_state), m_arrow(t_arrow), m_label(t_label)
{}

// Destructor
Transition::~Transition()
{}

// Converts Transition to a string
std::string Transition::toString()
{
	if (m_arrow.m_corners.size() < 3) return "";
	return "T," +
		std::to_string(m_first_state.m_circle.m_label) + "," +
		std::to_string(m_next_state.m_circle.m_label) + "," + 
		m_label + "," +
		std::to_string(m_arrow.m_start.x) + "," +
		std::to_string(m_arrow.m_start.y) + "," + 
		std::to_string(m_arrow.m_end.x) + "," + 
		std::to_string(m_arrow.m_end.y) + "\n";
}
