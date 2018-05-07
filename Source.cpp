#include <iostream>
#include "SketchAnalyzer.h"

int main(int argc, const char** argv)
{
	if (argc < 1) return 0;

	SketchAnalyzer sa;

	std::cout << "Loading image..." << std::endl;
	sa.loadImage(argv[1], std::strlen(argv[1]));
	std::cout << "Finding components..." << std::endl;
	sa.findConnectedComponents();
	std::cout << "Finding containers..." << std::endl;
	sa.findContainers();
	std::cout << "Finding circles..." << std::endl;
	sa.findCircles();
	std::cout << "Finding characters..." << std::endl;
	sa.findCharacters();
	std::cout << "Finding arrows..." << std::endl;
	sa.findArrows();
	std::cout << "Parsing labels..." << std::endl;
	sa.parseLabels();
	std::cout << "Creating states..." << std::endl;
	sa.createStates();
	std::cout << "Creating transitions..." << std::endl;
	sa.createTransitions();
	std::cout << "Creating output.txt..." << std::endl;
	sa.outputFile();

	return 0;
}