#pragma once

#include "State.h"
#include "Arrow.h"

class Transition
{
private:

public:
	State m_first_state;
	State m_next_state;
	std::string m_label;

	Arrow m_arrow;


	Transition(State& t_first_state, State& t_next_state, Arrow& t_arrow, std::string t_label); // Constructor
	~Transition(); // Destructor

	std::string toString(); // Converts Transition to a string
};