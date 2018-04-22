#include "ImageProcessor.h"
#include <iostream>

ImageProcessor::ImageProcessor(std::string t_imagePath)
{
	m_image = cv::imread(t_imagePath, 0);
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

cv::Mat ImageProcessor::forComponentDetector()
{
	cv::Mat binary_image = m_image.clone();
	cv::threshold(binary_image, binary_image, 170, 255, cv::THRESH_BINARY);
	return binary_image;
}

cv::Mat ImageProcessor::containerImage(Container & t_container, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image, t_container.m_container->getBoundingBox());

	cv::Mat container_image = cv::Mat(labeled_image.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 0, 0) };
	for (int r = 0; r < container_image.rows; ++r)
	{
		for (int c = 0; c < container_image.cols; ++c)
		{
			int label = labeled_image.at<int>(r, c);
			cv::Vec3b &pixel = container_image.at<cv::Vec3b>(r, c);
			if (label == t_container.m_container->m_label || label == t_container.getChildLabels())
			{
				pixel = colors[1];
			}
			else
			{
				pixel = colors[0];
			}
		}
	}
	return container_image;
}

std::vector<cv::Vec4i> ImageProcessor::getHierarchy(Container& t_container, cv::Mat t_labeled_image)
{
	cv::Mat image, image_gray, canny_output;
	image = containerImage(t_container, t_labeled_image);
	cv::cvtColor(image, image_gray, CV_BGR2GRAY);
	cv::blur(image_gray, image_gray, cv::Size(3, 3));
	cv::Canny(image_gray, canny_output, 100, 200, 3);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	return hierarchy;
}
