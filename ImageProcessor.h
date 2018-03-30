#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
};