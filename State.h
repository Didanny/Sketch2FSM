#pragma once

#include "Component.h"
#include "ComponentDetector.h"

#include <string>

class State
{
private:

public:
	std::string m_name;
	Component& m_circle;
	bool m_is_accept;

	State(Component t_component, std::string t_name); // Constructor
	~State(); // Destructor

	void setAccept(); // Sets state as accept state
	double getRadius(); // Returns radius of circle
};