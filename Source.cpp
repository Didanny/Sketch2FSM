#include <iostream>
#include "SketchAnalyzer.h"

const char* keys =
{
	"{help h||}{@image|../data/stuff.jpg|image for converting to a grayscale}"
};

std::vector<int> vect;
std::vector<int>& Vect()
{
	return vect;
}

int main(int argc, const char** argv)
{
	SketchAnalyzer sa;
	std::cout << argv[1] << "\n";
	sa.loadImage(argv[1], std::strlen(argv[1]));
	sa.findConnectedComponents();
	sa.findContainers();
	sa.findCircles();
	sa.findCharacters();
	sa.findArrows();
	sa.parseLabels();
	sa.createStates();
	sa.createTransitions();
	sa.outputFile();

	std::cout << "CONTAINERS\n";
	for (int i = 0; i < sa.m_circle_classifier->getContainers().size(); i++)
	{
		std::cout << sa.m_circle_classifier->getContainers().at(i).m_container->m_label << std::endl;
	}
	std::cout << "CIRCLES\n";
	for (int i = 0; i < sa.m_circles->getLabels().size(); i++)
	{
		std::cout << sa.m_circles->getLabels().at(i) << std::endl;
	}
	std::cout << "CHARS\n";
	for (int i = 0; i < sa.m_chars.getLabels().size(); i++)
	{
		std::cout << sa.m_chars.getLabels().at(i) << std::endl;
	}
	std::cout << "ARROWS\n";
	std::cout << "This many arrows " << sa.m_arrow_classifier->m_arrows_i.size()
	<< sa.m_arrow_classifier->m_arrows.size() << "\n";
	for (int i = 0; i < sa.m_circles->getLabels().size(); i++)
	{
		std::cout << sa.m_circles->getLabels().at(i) << std::endl;
	}
	std::cout << "ARROW CHARS\n";
	for (int i = 0; i < sa.m_arrow_classifier->getLabelLabels().size(); i++)
	{
		std::cout << "Arrow " << i << std::endl;
	}
	std::cout << "STATES\n";
	for (int i = 0; i < sa.m_states.size(); i++)
	{
		std::cout << sa.m_states.at(i).m_name << " " << sa.m_states.at(i).m_circle.m_label << " " << sa.m_states.at(i).m_circle.getCentroid().y << "," << sa.m_states.at(i).m_circle.getCentroid().x << std::endl;
	}
	std::cout << "TRANSITIONS\n";
	for (int i = 0; i < sa.m_transitions.size(); i++)
	{
		std::cout << sa.m_transitions.at(i).m_label << std::endl;
	}

	return 0;
}