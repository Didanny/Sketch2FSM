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
	bool m_is_enclosed; // true if component is entirely within another component
	Component* m_container; // The smallest component that encloses this component
	bool m_is_container; // true if component is container
public:
	int m_label;
	Component(int t_x, int t_y, int t_width, int t_height, int t_area, double t_cx, double t_cy, int t_label); // Constructor
	~Component(); // Destructor
	cv::Rect getBoundingBox(); // Returns the bounding box of the component
	int getArea(); // Returns the are in pixels
	bool contains(Component& t_component); // Returns true if this bounding box is completely within the t_component bounding box
	void setContainer(Component& t_component); // Sets m_container to t_component
	Component* getContainer(); // Returns pointer to the container
	cv::Point getCentroid(); // Returns the centroid
	Component copy(); // Returns a copy of the component
	int getLabel(); // Returns label
	bool equals(Component t_component); // Returns true if equal
	bool operator<(Component& t_right); // Returns true if label less than
	void setAsContainer(); // Sets the surrent component as a container
	bool isContainer(); // Returns true if component is container
};

bool operator== (Component t_lhs, Component t_right); // Returns true if equal
bool operator< (Component t_lhs, Component t_right); // Returns true if label less than, no logical purpose just to enable sorting
