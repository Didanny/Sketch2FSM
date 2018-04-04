#include "ComponentDetector.h"

#define INIT(x, y, width, height, area, centroid_x, centroid_y) int x = stats.at<int>(cv::Point(0, i)); \
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
		INIT(x, y, width, height, area, centroid_x, centroid_y);

		if (area >= 10 && height != m_original_image.rows && width != m_original_image.cols)
		{
			Component component(x, y, width, height, area, centroid_x, centroid_y);
			m_components.push_back(component);
		}
	}
}

Components& ComponentDetector::getComponents()
{
	return m_components;
}

void ComponentDetector::findContainers()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		for (int j = 0; j < m_components.size(); j++)
		{
			if (m_components.at(j).contains(m_components.at(i)))
			{
				if (m_components.at(i).getContainer() != NULL)
				{
					if (m_components.at(i).getContainer()->getBoundingBox().area() > m_components.at(j).getBoundingBox().area())
					{
						m_components.at(i).setContainer(m_components.at(j));
					}
				}
				else
				{
					m_components.at(i).setContainer(m_components.at(j));
				}
			}
		}
	}
}
