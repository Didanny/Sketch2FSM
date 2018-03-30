#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(std::string t_imagePath)
{
	m_image = cv::imread(t_imagePath);
}

ImageProcessor::~ImageProcessor() {}

cv::Mat ImageProcessor::originalImage()
{
	return m_image;
}

cv::Mat ImageProcessor::forCircleDetector()
{
	cv::Mat imageGray;
	cv::cvtColor(m_image, imageGray, CV_BGR2GRAY);
	cv::GaussianBlur(imageGray, imageGray, cv::Size(9, 9), 2, 2);
	return imageGray;
}