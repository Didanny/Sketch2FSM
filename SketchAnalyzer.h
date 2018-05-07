#pragma once

#include <fstream>
#include <iostream>

#include "ImageProcessor.h"
#include "CircleClassifier.h"
#include "Circle.h"
#include "CharacterClassifier.h"
#include "ArrowClassifier.h"
#include "State.h"
#include "Transition.h"

struct SketchAnalyzer
{
	ImageProcessor* m_image_processor; // Image processor to do all the image creation
	ComponentDetector* m_component_detector; // Components detetor to find the components
	CircleClassifier* m_circle_classifier; // circle classifier to find the circles
	Circles* m_circles; // stores the circles
	ArrowClassifier* m_arrow_classifier; // classifies the arrows and intializes themm

	CharacterClassifier m_chars; // finds and classifies the characters
	Components m_components; // Vector of the connected components

	std::vector<State> m_states; // Vector of states
	std::vector<Transition> m_transitions; // Vector of transitions

	std::vector<std::string> m_created_files; // Vector of created files

	SketchAnalyzer(); // Constructor
	~SketchAnalyzer(); // Destructor

	std::string readLabel(std::string t_file); // Read text file and return string

	void loadImage(const char* t_image_path, int t_length); // Loads image from given path
	void findConnectedComponents(); // Detects connected components
	void findContainers(); // Finds the containers, circle candidates
	void findCircles(); // Finds the circles among the containers
	void findCharacters(); // Finds the characters in and out of the circles
	void findArrows(); // Finds the arrows
	void parseLabels(); // Converts the labels to text
	void createStates(); // Converts the circles to states
	void createTransitions(); // Converts the arrows to transitions
	void outputFile(); // Outputs the States and Transitions to a text file
};