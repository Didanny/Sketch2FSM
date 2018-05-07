#pragma once

#include "Component.h"
#include "ComponentDetector.h"

#include <string>

struct State
{
	std::string m_name; // Label of the state
	bool m_is_accept; // True if the state is an accept state

	Component m_circle; // Circle of the state

	State(Component& t_component, std::string t_name); // Constructor
	~State(); // Destructor

	void setAccept(); // Sets state as accept state
	double getRadius(); // Returns radius of circle

	std::string toString(); // Converts State to string
};