//#pragma once
//
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <vector>
//#include <iostream>
//
//typedef cv::Vec3f Circle;
//typedef std::vector<Circle> Circles;
//
//static int CENTER_X = 0;
//static int CENTER_Y = 1;
//static int RADIUS = 2;
//
//class CircleDetector
//{
//private:
//	cv::Mat m_image;
//public:
//	CircleDetector(cv::Mat t_image); // Constructor, takes processed image from ImageProcessor
//	~CircleDetector(); // Destructor
//	Circles detectCircles(float t_maxRadius); // Detects all circles with radius < t_maxRadius
//	Circles detectAllCircles(); // Detects all circles in m_image
//	float getMinRadius(Circles t_circles, float t_min); // Loops thru circles to find min radius
//	Circles removeDuplicates(Circles t_circles); // Removes duplicate circles
//	bool areDuplicates(Circle t_circle1, Circle t_circle2); // Returns true if t_circle1 and t_circle2 are duplicates
//};
//
//Circles operator+ (const Circles& lhs, const Circles& rhs);
//
