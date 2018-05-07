#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Container.h"
#include "Arrow.h"

struct ImageProcessor
{
	cv::Mat m_image; // The original image loaded

	ImageProcessor(std::string t_imagePath); // Constructor, takes image from user sets it to _image
	~ImageProcessor(); // Destructor

	cv::Mat forComponentDetector(); // Returns a processed image for the ComponentDetector object
	cv::Mat containerImage(Container& t_container, cv::Mat t_labeled_image); // Returns an image of just the container and children
	cv::Mat childrenImage(Container& t_container, cv::Mat t_labeled_image); // Returns an image of just the children of the container
	cv::Mat componentImage(Component& t_component, cv::Mat t_labeled_image); // Returns an image of just the given component
	cv::Mat arrowImage(Arrow& t_arrow, Component & t_component, cv::Mat t_labeled_image); // Returns an image of the arrow with it's end and start points
	cv::Mat arrowLabelImage(Arrow& t_arrow, cv::Mat t_labeled_image); // Returns and image of an arrow's label
	cv::Mat labelIMage(std::vector<int> t_labels, cv::Mat t_labeled_image); // Returns an image of the components with the given labels

	std::vector<cv::Vec4i> getHierarchy(Container & t_container, cv::Mat t_labeled_image); // Returns the contour hierarchy of an container
	std::vector<cv::Point2f> getFeatures(cv::Mat t_arrow); // Finds the corners of an image, and returns the corners vector of an image
};