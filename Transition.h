#pragma once

#include "State.h"

class Transition
{
private:

public:
	State m_first_state;
	State m_next_state;
	std::string m_label;

	Component m_arrow;


	Transition(State& t_first_state, State& t_next_state, Component& t_arrow, std::string t_label); // Constructor
	~Transition(); // Destructor
};