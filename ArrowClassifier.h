#pragma once

#include "CharacterClassifier.h"
#include "ImageProcessor.h"
#include "Arrow.h"

struct ArrowClassifier
{
	Components m_arrows; // Vector of components representing arrows
	std::vector<Arrow> m_arrows_i; // Vector of arrows

	ArrowClassifier(Components& t_components, std::vector<int> t_labels); // Constructor
	~ArrowClassifier(); // Destructor

	std::vector<int> getLabels(); // Returns vector of labels of the arrows 
	void initArrows(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector); // Initialize the m_arrows_i vector
	void initArrowLabels(Components& t_chars); // Finds the closest arrow to each character and links them
	std::vector<int> getLabelLabels(); // Returns vector of labels of the arrow characters
	void initPaths(std::vector<State>& t_states); // Initializes the states of each arrow
};