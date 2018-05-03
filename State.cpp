#include "State.h"

State::State(Component t_component, std::string t_name)
	: m_circle(t_component), m_name(t_name), m_is_accept(false)
{
}

State::~State()
{
}

void State::setAccept()
{
	m_is_accept = true;
}
