#include "ComponentDetector.h"

#define init(x, y, width, height, area, centroid_x, centroid_y) int x = stats.at<int>(cv::Point(0, i)); \
		int y = stats.at<int>(cv::Point(1, i)); \
		int width = stats.at<int>(cv::Point(2, i)); \
		int height = stats.at<int>(cv::Point(3, i)); \
		int area = stats.at<int>(cv::Point(4, i)); \
		double centroid_x = centroids.at<double>(i, 0); \
		double centroid_y = centroids.at<double>(i, 1);

ComponentDetector::ComponentDetector(cv::Mat t_image)
	: m_original_image(t_image)
{
	m_labeled_image = cv::Mat(m_original_image.size(), CV_32S);
}

ComponentDetector::~ComponentDetector()
{}

void ComponentDetector::detectComponents()
{
	cv::Mat bw = m_original_image < 100;
	cv::Mat stats;
	cv::Mat centroids;
	cv::connectedComponentsWithStats(bw, m_labeled_image, stats, centroids);
	for (int i = 0; i < stats.rows; i++)
	{
		init(x, y, width, height, area, centroid_x, centroid_y);

		if (area >= 10)
		{
			Component component(x, y, width, height, area, centroid_x, centroid_y);
			m_components.push_back(component);
		}
	}
}
