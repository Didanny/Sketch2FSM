#pragma once

#include "Container.h"
#include "ImageProcessor.h"

//typedef std::vector<Container> Containers;
class Containers : public std::vector<Container>
{
public:
	int indexOf(Container t_container); // Returns index of t_container, -1 if not found
};

class CircleClassifier 
{
private:
	Containers m_containers;
	cv::Mat m_labeled_image;
public:
	CircleClassifier(cv::Mat t_labeled_image); // Constructor
	~CircleClassifier(); // Destructor
	void initContainers(Components& t_components); // initializes the containers
	void initChildren(Components& t_components); // initializes the children on m_containers
	bool isCircle(Container t_container, std::vector<cv::Vec4i>& t_hierarchy); // returns true if the container is in fact a circle
	Containers getContainers(); // Returns containers
	Containers findCircles(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector); // Returns the containers that are circles
	void showCircles(); // Shows the circles in new window
	void displayContainerLabels(); // Displays container labels
};