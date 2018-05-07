#pragma once

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

//#include "C#\sketch2fsmlib\stdafx.h"


struct Component
{

	cv::Rect m_bounding_box; // The bounding box of a component
	int m_area; // The area of the component in pixels
	cv::Point m_centroid; // The centroid of the components
	Component* m_container; // The smallest component that encloses this component
	int m_label; // The label given to component by cv::connectedComponents
	bool m_is_container; // True if component is container;

	Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy, int t_label); // Constructor
	~Component(); // Destructor
	//cv::Rect m_bounding_box; // Returns the bounding box of the component
	//int m_area; // Returns the are in pixels
	bool contains(Component& t_component); // Returns true if this bounding box is completely within the t_component bounding box
	void setContainer(Component& t_component); // Sets m_container to t_component
	Component* getContainer(); // Returns pointer to the container
	cv::Point getCentroid(); // Returns the centroid
	Component copy(); // Returns a copy of the component
	bool isContainer();
	void setAsContainer();
	//int m_label; // Returns label
};