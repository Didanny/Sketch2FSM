#pragma once

#include "State.h"
#include "Arrow.h"

struct Transition
{
	State m_first_state; // The state the transition starts at
	State m_next_state; // The next state if the transition succeeds
	std::string m_label; // The label of the arrow

	Arrow m_arrow; // The arrow representing this transition

	Transition(State& t_first_state, State& t_next_state, Arrow& t_arrow, std::string t_label); // Constructor
	~Transition(); // Destructor

	std::string toString(); // Converts Transition to a string
};