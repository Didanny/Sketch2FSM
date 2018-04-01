#pragma once

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

class Component
{
private:
	cv::Rect m_bounding_box; // The bounding box of a component
	int m_area; // The area of the component in pixels
	cv::Point m_centroid; // The centroid of the components
	bool is_enclosed; // true if component is entirely within another component
public:
	Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy); // Constructor
	~Component(); // Destructor
	cv::Rect getBoundingBox();
};