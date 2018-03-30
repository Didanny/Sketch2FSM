//#include "CircleDetector.h"
//
//CircleDetector::CircleDetector(cv::Mat t_image)
//	: m_image(t_image)
//{
//}
//
//
//CircleDetector::~CircleDetector()
//{
//}
//
//Circles CircleDetector::detectCircles(float t_maxRadius)
//{
//	Circles circles;
//	cv::HoughCircles(m_image, circles, CV_HOUGH_GRADIENT, 1, m_image.rows / 8, 200, 60, 0, t_maxRadius);
//	return circles;
//}
//
//float CircleDetector::getMinRadius(Circles t_circles, float t_min)
//{
//	for (int i = 0; i < t_circles.size(); i++)
//	{
//		if (t_circles[i][RADIUS] < t_min)
//		{
//			t_min = t_circles[i][RADIUS];
//		}
//	}
//	return t_min;
//}
//
//Circles CircleDetector::removeDuplicates(Circles t_circles)
//{
//	for (int i = 0; i < t_circles.size(); i++)
//	{
//		int j = i + 1;
//		while (j < t_circles.size()) {
//			if (areDuplicates(t_circles.at(i), t_circles.at(j))) {
//				std::cout << t_circles.at(i)[RADIUS] << ":: " << t_circles.at(j)[RADIUS] << std::endl;
//				t_circles.erase(t_circles.begin() + j);
//				j--;
//			}
//			j++;
//			int x;
//			//std::cin >> x;
//		}
//	}
//	return t_circles;
//}
//
//bool CircleDetector::areDuplicates(Circle t_circle1, Circle t_circle2)
//{
//	float threshhold = 0.01;
//	float radiiDifference = std::abs(t_circle1[RADIUS] - t_circle2[RADIUS]);
//	float centerXdifference = std::abs(t_circle1[CENTER_X] - t_circle2[CENTER_X]);
//		float centerYdifference = std::abs(t_circle1[CENTER_Y] - t_circle2[CENTER_Y]);
//	if (radiiDifference > t_circle1[RADIUS] * threshhold &&
//		centerXdifference > t_circle1[CENTER_X] * threshhold &&
//		centerYdifference > t_circle1[CENTER_Y] * threshhold)
//	{
//		return false;
//	}
//	return true;
//}
//
//Circles CircleDetector::detectAllCircles()
//{
//	Circles circles;
//	float newMin, oldMin;
//	newMin = std::max(m_image.rows, m_image.cols);
//	std::cout << m_image.rows << "::" << m_image.cols << std::endl;
//	do
//	{
//		oldMin = newMin;
//		circles = circles + detectCircles(newMin);
//		newMin = getMinRadius(circles, newMin);
//	} while (oldMin != newMin);
//	// return circles;
//	return removeDuplicates(circles);
//}
//
//Circles operator+ (const Circles& lhs, const Circles& rhs)
//{
//	Circles y = lhs;
//	for (int i = 0; i < rhs.size(); i++)
//	{
//		y.push_back(rhs.at(i));
//	}
//	return y;
//}


