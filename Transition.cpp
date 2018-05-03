#include "Transition.h"

Transition::Transition(State & t_first_state, State & t_next_state, Component & t_arrow, std::string t_label)
	: m_first_state(t_first_state), m_next_state(t_next_state), m_arrow(t_arrow), m_label(t_label)
{
}

Transition::~Transition()
{
}
