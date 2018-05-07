#include "ComponentDetector.h"

#define INIT(x, y, width, height, area, centroid_x, centroid_y) int x = stats.at<int>(cv::Point(0, i)); \
		int y = stats.at<int>(cv::Point(1, i)); \
		int width = stats.at<int>(cv::Point(2, i)); \
		int height = stats.at<int>(cv::Point(3, i)); \
		int area = stats.at<int>(cv::Point(4, i)); \
		double centroid_x = centroids.at<double>(i, 0); \
		double centroid_y = centroids.at<double>(i, 1);

// Constructor
ComponentDetector::ComponentDetector(cv::Mat t_image)
	: m_original_image(t_image)
{
	m_labeled_image = cv::Mat(m_original_image.size(), CV_32S);
}

// Destructor
ComponentDetector::~ComponentDetector()
{}

// Finds the components with cv::connectedComponentsWithStats
void ComponentDetector::detectComponents()
{
	cv::Mat bw = m_original_image < 100;
	cv::Mat stats;
	cv::Mat centroids;
	cv::connectedComponentsWithStats(bw, m_labeled_image, stats, centroids);
	// Iterate over the vectors provided by the algorithm and store them as components
	// Add them to the m_components vector
	for (int i = 0; i < stats.rows; i++)
	{
		INIT(x, y, width, height, area, centroid_x, centroid_y);

		if (area >= 10 && height != m_original_image.rows && width != m_original_image.cols)
		{
			Component component(x, y, width, height, area, centroid_x, centroid_y, i);
			m_components.push_back(component);
		}
	}
}

// Sets the container for each component
void ComponentDetector::findContainers()
{
	// Iterate of the components
	for (int i = 0; i < m_components.size(); i++)
	{
		// Iterate over every pair of components
		for (int j = 0; j < m_components.size(); j++)
		{
			// Check if one contains the other
			if (m_components.at(j).contains(m_components.at(i)))
			{
				// If yes, set the parent as a container
				m_components.at(j).setAsContainer();
				// Now check if this is the smalles container of this child
				// If not keep the child's parent unchanged, else set this
				// parent to be the container of the child
				if (m_components.at(i).m_container != NULL)
				{
					if (m_components.at(i).m_container->m_bounding_box.area() > m_components.at(j).m_bounding_box.area())
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


