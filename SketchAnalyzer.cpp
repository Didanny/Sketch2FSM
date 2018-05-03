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

std::string SketchAnalyzer::readLabel(std::string t_file)
{
	std::string line;
	std::ifstream lbl_file(t_file);
	if (lbl_file.is_open())
	{
		std::getline(lbl_file, line);
		//std::cout << line;
	}
	return line;
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
	m_arrow_classifier->initArrowLabels(m_chars.m_chars_unclassified);
}

void SketchAnalyzer::parseLabels()
{
	for (int i = 0; i < m_circles->getCircles().size(); i++)
	{
		cv::Mat container_image = m_image_processor->childrenImage(m_circles->getCircles().at(i), m_component_detector->getLabeledImage());
		int label = m_circles->getCircles().at(i).m_container->getLabel();
		cv::imwrite("./temp/lbl" + std::to_string(label) + ".png", container_image);

		std::string command = "tesseract ./temp/lbl" + std::to_string(label) + ".png ./temp/lbl" + std::to_string(label) + " -l eng";
		system(command.c_str());
	}
	for (int i = 0; i < m_arrow_classifier->m_arrows_i.size(); i++)
	{
		for (int j = 0; j < m_arrow_classifier->m_arrows_i.at(i).m_labels.size(); j++)
		{
			Component character = m_arrow_classifier->m_arrows_i.at(i).m_labels.at(j);
			cv::Mat char_image = m_image_processor->componentImage(m_arrow_classifier->m_arrows_i.at(i).m_labels.at(j), m_component_detector->getLabeledImage());
			int label = character.getLabel();
			cv::imwrite("./temp/lbl" + std::to_string(label) + ".png", char_image);

			std::string command = "tesseract ./temp/lbl" + std::to_string(label) + ".png ./temp/lbl" + std::to_string(label) + " -l eng";
			system(command.c_str());
		}
	}
}

void SketchAnalyzer::createStates()
{
	int accept = m_circles->m_accept_index;
	std::string path = "./temp/lbl";
	for (int i = 0; i < m_circles->getCircles().size(); i++)
	{
		Component circle = *(m_circles->getCircles().at(i).m_container);
		int lbl = circle.getLabel();
		std::string label = readLabel(path + std::to_string(lbl) + ".txt");
		State state(circle, label);
		if (i == accept) state.setAccept();
		m_states.push_back(state);
	}
}

void SketchAnalyzer::createTransitions()
{
	m_arrow_classifier->initPaths(m_states);
}
