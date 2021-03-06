#include "ImageProcessor.h"
#include <iostream>

// Constructor
ImageProcessor::ImageProcessor(std::string t_imagePath)
{
	m_image = cv::imread(t_imagePath, 0);
}

// Destructor
ImageProcessor::~ImageProcessor() 
{}

// Returns a processed image for the ComponentDetector object
cv::Mat ImageProcessor::forComponentDetector()
{
	cv::Mat binary_image = m_image.clone();
	cv::threshold(binary_image, binary_image, 170, 255, cv::THRESH_BINARY);
	return binary_image;
}

// Returns an image of just the container and children
cv::Mat ImageProcessor::containerImage(Container & t_container, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image, t_container.m_container->m_bounding_box);

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

// Returns an image of just the children of the container
cv::Mat ImageProcessor::childrenImage(Container & t_container, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image, t_container.m_container->m_bounding_box);

	cv::Mat container_image = cv::Mat(labeled_image.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 0, 0) };
	for (int r = 0; r < container_image.rows; ++r)
	{
		for (int c = 0; c < container_image.cols; ++c)
		{
			int label = labeled_image.at<int>(r, c);
			cv::Vec3b &pixel = container_image.at<cv::Vec3b>(r, c);
			if (label == t_container.getChildLabels())
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

// Returns an image of just the given component
cv::Mat ImageProcessor::componentImage(Component & t_component, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image, t_component.m_bounding_box);

	cv::Mat component_image = cv::Mat(labeled_image.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 0, 0) };
	for (int r = 0; r < component_image.rows; ++r)
	{
		for (int c = 0; c < component_image.cols; ++c)
		{
			int label = labeled_image.at<int>(r, c);
			cv::Vec3b &pixel = component_image.at<cv::Vec3b>(r, c);
			if (label == t_component.m_label)
			{
				pixel = colors[1];
			}
			else
			{
				pixel = colors[0];
			}
		}
	}
	return component_image;
}

// Returns an image of the arrow with it's end and start points
cv::Mat ImageProcessor::arrowImage(Arrow & t_arrow, Component & t_component, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image, t_component.m_bounding_box);
	cv::Mat component_image = componentImage(t_component, t_labeled_image);

	cv::circle(component_image, t_arrow.m_start, 4, cv::Scalar(0, 255, 0), -1, 8, 0);
	cv::circle(component_image, t_arrow.m_end, 4, cv::Scalar(0, 0, 255), -1, 8, 0);

	return component_image;
}

// Returns and image of an arrow's label
cv::Mat ImageProcessor::arrowLabelImage(Arrow & t_arrow, cv::Mat t_labeled_image)
{
	std::vector<int> labels = t_arrow.getLabelLabels();
	int max_x = 0;
	int max_y = 0;
	int min_x = 99999999;
	int min_y = 99999999;

	for (int i = 0; i < t_arrow.m_labels.size(); i++)
	{
		int my_min_x = t_arrow.m_labels.at(i).m_bounding_box.x;
		int my_min_y = t_arrow.m_labels.at(i).m_bounding_box.y;
		int my_max_x = t_arrow.m_labels.at(i).m_bounding_box.x + t_arrow.m_labels.at(i).m_bounding_box.width;
		int my_max_y = t_arrow.m_labels.at(i).m_bounding_box.y + t_arrow.m_labels.at(i).m_bounding_box.height;
		if (max_x < my_max_x) max_x = my_max_x;
		if (max_y < my_max_y) max_y = my_max_y;
		if (min_x > my_min_x) min_x = my_min_x;
		if (min_y > my_min_y) min_y = my_min_y;
	}

	cv::Rect rect(min_x, min_y, max_x - min_x, max_y - min_y);
	cv::Mat labeled_image = cv::Mat(t_labeled_image, rect);

	cv::Mat component_image = cv::Mat(labeled_image.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 0, 0) };
	for (int r = 0; r < component_image.rows; ++r)
	{
		for (int c = 0; c < component_image.cols; ++c)
		{
			int label = labeled_image.at<int>(r, c);
			cv::Vec3b &pixel = component_image.at<cv::Vec3b>(r, c);
			if (label == labels)
			{
				pixel = colors[1];
			}
			else
			{
				pixel = colors[0];
			}
		}
	}
	return component_image;
}

// Returns an image of the components with the given labels
cv::Mat ImageProcessor::labelIMage(std::vector<int> t_labels, cv::Mat t_labeled_image)
{
	cv::Mat labeled_image = cv::Mat(t_labeled_image);
	cv::Mat component_image = cv::Mat(labeled_image.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 0, 0) };
	for (int r = 0; r < component_image.rows; ++r)
	{
		for (int c = 0; c < component_image.cols; ++c)
		{
			int label = labeled_image.at<int>(r, c);
			cv::Vec3b &pixel = component_image.at<cv::Vec3b>(r, c);
			if (label == t_labels)
			{
				pixel = colors[1];
			}
			else
			{
				pixel = colors[0];
			}
		}
	}
	return component_image;
}

// Returns the contour hierarchy of an container
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

// Finds the corners of an image, and returns the corners vector
std::vector<cv::Point2f> ImageProcessor::getFeatures(cv::Mat t_arrow)
{
	std::vector<cv::Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	cv::Mat arrow_grey;
	cv::cvtColor(t_arrow, arrow_grey, CV_BGR2GRAY);

	goodFeaturesToTrack(arrow_grey, corners, 100, qualityLevel, minDistance, cv::Mat(), blockSize, useHarrisDetector, k);
	return corners;
}
