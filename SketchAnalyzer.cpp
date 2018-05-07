#include "SketchAnalyzer.h"

// Constructor
SketchAnalyzer::SketchAnalyzer()
{}

// Destructor
SketchAnalyzer::~SketchAnalyzer()
{
	delete m_image_processor;
	delete m_component_detector;
	delete m_circle_classifier;
	delete m_circles;
	delete m_arrow_classifier;
	for (int i = 0; i < m_created_files.size(); i++)
	{
		std::remove(m_created_files.at(i).c_str());
	}
}

// Read text file and return string
std::string SketchAnalyzer::readLabel(std::string t_file)
{
	std::string line;
	std::ifstream lbl_file(t_file);
	if (lbl_file.is_open())
	{
		std::getline(lbl_file, line);
	}
	else
	{
		return "unknown";
	}
	return line;
}

// Loads image from given file path
void SketchAnalyzer::loadImage(const char* t_image_path, int t_length)
{
	std::string image_path(t_image_path, t_length);
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
	m_circle_classifier = new CircleClassifier(m_component_detector->m_labeled_image);
	m_circle_classifier->initContainers(m_component_detector->m_components);
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
	m_chars.findChars(m_component_detector->m_components);
}

// Finds the arrows
void SketchAnalyzer::findArrows()
{
	std::vector<int> labels_all = m_circles->getLabels();
	std::vector<int> labels = m_chars.getLabels();
	labels_all.insert(labels_all.end(), labels.begin(), labels.end());

	m_arrow_classifier = new ArrowClassifier(m_component_detector->m_components, labels_all);
	m_arrow_classifier->initArrows(*m_image_processor, *m_component_detector);
	m_arrow_classifier->initArrowLabels(m_chars.m_chars_unclassified);

	m_circles->initAcceptIndex();
}

// Converts the labels to text
void SketchAnalyzer::parseLabels()
{
	for (int i = 0; i < m_circles->m_circles.size(); i++)
	{
		cv::Mat container_image = m_image_processor->childrenImage(m_circles->m_circles.at(i), m_component_detector->m_labeled_image);
		int label = m_circles->m_circles.at(i).m_container->m_label;
		cv::imwrite("./temp/lbl" + std::to_string(label) + ".png", container_image);

		m_created_files.push_back("./temp/lbl" + std::to_string(label) + ".png");
		m_created_files.push_back("./temp/lbl" + std::to_string(label) + ".txt");

		std::string command = "tesseract ./temp/lbl" + std::to_string(label) + ".png ./temp/lbl" + std::to_string(label) + " -l eng";
		system(command.c_str());
	}
	for (int i = 0; i < m_arrow_classifier->m_arrows_i.size(); i++)
	{
		for (int j = 0; j < m_arrow_classifier->m_arrows_i.at(i).m_labels.size(); j++)
		{
			Component character = m_arrow_classifier->m_arrows_i.at(i).m_labels.at(j);
			cv::Mat char_image = m_image_processor->arrowLabelImage(m_arrow_classifier->m_arrows_i.at(i), m_component_detector->m_labeled_image);
			int label = m_arrow_classifier->m_arrows_i.at(i).m_arrow.m_label;
			cv::imwrite("./temp/lbl" + std::to_string(label) + ".png", char_image);

			m_created_files.push_back("./temp/lbl" + std::to_string(label) + ".png");
			m_created_files.push_back("./temp/lbl" + std::to_string(label) + ".txt");

			std::string command = "./tesseract ./temp/lbl" + std::to_string(label) + ".png ./temp/lbl" + std::to_string(label) + " -l eng";
			system(command.c_str());
		}
	}
}

// Converts the circles to states
void SketchAnalyzer::createStates()
{
	int accept = m_circles->m_accept_index;
	std::string path = "./temp/lbl";
	for (int i = 0; i < m_circles->m_circles.size(); i++)
	{
		Component circle = *(m_circles->m_circles.at(i).m_container);
		int lbl = circle.m_label;
		std::string label = readLabel(path + std::to_string(lbl) + ".txt");
		State state(*(m_circles->m_circles.at(i).m_container), label);
		if (i == accept) state.setAccept();
		m_states.push_back(state);
	}
}

// Converts the arrows to transitions
void SketchAnalyzer::createTransitions()
{
	m_arrow_classifier->initPaths(m_states);
	for (int i = 0; i < m_arrow_classifier->m_arrows.size(); i++)
	{
		std::string path = "./temp/lbl";

		State* source = m_arrow_classifier->m_arrows_i.at(i).m_source;
		State* destination = m_arrow_classifier->m_arrows_i.at(i).m_destination;

		int lbl = m_arrow_classifier->m_arrows_i.at(i).m_arrow.m_label;

		std::string label = readLabel(path + std::to_string(lbl) + ".txt");

		Transition transition(*source, *destination, m_arrow_classifier->m_arrows_i.at(i), label);
		m_transitions.push_back(transition);
	}
}

// Outputs the States and Transitions to a text file
void SketchAnalyzer::outputFile()
{
	std::ofstream output;
	output.open("./output.txt");
	output << m_image_processor->m_image.cols << "," << m_image_processor->m_image.rows << "\n";
	for (int i = 0; i < m_states.size(); i++)
	{
		output << m_states.at(i).toString();// << "\n";
	}
	for (int i = 0; i < m_transitions.size(); i++)
	{
		output << m_transitions.at(i).toString();// << "\n";
	}
	output.close();
}
