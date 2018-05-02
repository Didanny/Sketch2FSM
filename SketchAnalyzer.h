#pragma once

#include "ImageProcessor.h"
#include "CircleClassifier.h"
#include "Circle.h"
#include "ComponentsWithStats.h"
#include "ArrowClassifier.h"
#include "State.h"

class SketchAnalyzer
{
private:
	//ImageProcessor* m_image_processor;
public:
	ImageProcessor* m_image_processor;
	ComponentDetector* m_component_detector;
	CircleClassifier* m_circle_classifier;
	Circles* m_circles;
	ArrowClassifier* m_arrow_classifier;

	CharacterClassifier m_chars;
	Components m_components; // Vector of the connected components

	std::vector<State> m_states;

	SketchAnalyzer(); // Constructor
	~SketchAnalyzer(); // Destructor

	void loadImage(std::string t_image_path); // Loads image from given path
	void findConnectedComponents(); // Detects connected components
	void findContainers(); // Finds the containers, circle candidates
	void findCircles(); // Finds the circles among the containers
	void findCharacters(); // Finds the characters in and out of the circles
	void findArrows(); // Finds the arrows
	void parseLabels(); // Converts the labels to text
	void createStates(); // Converts the circles to states
};