#include "SketchAnalyzer.h"

// Constructor
SketchAnalyzer::SketchAnalyzer()
{}

SketchAnalyzer::~SketchAnalyzer()
{
	delete m_image_processor;
	delete m_component_detector;
	delete m_circle_classifier;
	delete m_circles;
	delete m_arrow_classifier;
}

// Loads image from given file path
void SketchAnalyzer::loadImage(std::string t_image_path)
{
	m_image_processor = new ImageProcessor(t_image_path);
}

// Detects the connected components
void SketchAnalyzer::findConnectedComponents()
{
	m_component_detector = new ComponentDetector(m_image_processor->forComponentDetector());
	m_component_detector->detectComponents();
}

// Detect the containers, circle candidates
void SketchAnalyzer::findContainers()
{
	m_component_detector->findContainers();
	m_circle_classifier = new CircleClassifier(m_component_detector->getLabeledImage());
	m_circle_classifier->initContainers(m_component_detector->getComponents());
}

// Finds the circles among the containers
void SketchAnalyzer::findCircles()
{
	Containers circles = m_circle_classifier->findCircles(*m_image_processor, *m_component_detector);
	m_circles = new Circles(circles);
}

// Finds the characters in and out of the circles
void SketchAnalyzer::findCharacters()
{
	m_chars = m_circles->getChars();
	m_chars.findChars(m_component_detector->getComponents());

	m_circles->initAcceptIndex();
}

// Finds the arrows
void SketchAnalyzer::findArrows()
{
	std::vector<int> labels_all = m_circles->getLabels();
	std::vector<int> labels = m_chars.getLabels();
	labels_all.insert(labels_all.end(), labels.begin(), labels.end());

	m_arrow_classifier = new ArrowClassifier(m_component_detector->getComponents(), labels_all);
	m_arrow_classifier->initArrows(*m_image_processor, *m_component_detector);
}
