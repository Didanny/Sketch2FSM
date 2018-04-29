#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Container.h"

class ImageProcessor
{
private:
	cv::Mat m_image;
public:
	//ImageProcessor(); // Default constructor
	ImageProcessor(std::string t_imagePath); // Constructor, takes image from user sets it to _image
	~ImageProcessor(); // Destructor
	cv::Mat originalImage(); // Return m_image
	cv::Mat forCircleDetector(); // Returns a processed image for the CircleDetectr object
	cv::Mat forComponentDetector(); // Returns a processed image for the ComponentDetector object
	cv::Mat containerImage(Container& t_container, cv::Mat t_labeled_image); // Returns an image of just the container and children
	std::vector<cv::Vec4i> getHierarchy(Container & t_container, cv::Mat t_labeled_image);
	cv::Mat componentImage(Component& t_component, cv::Mat t_labeled_image);
};