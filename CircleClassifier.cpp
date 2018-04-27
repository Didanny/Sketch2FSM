#include "CircleClassifier.h"
#include <iostream>

int Containers::indexOf(Container t_container)
{
	int label = t_container.m_container->getLabel();
	for (int i = 0; i < this->size(); i++)
	{
		if (this->at(i).m_container->getLabel() == label)
		{
			return i;
		}
	}
	return -1;
}

CircleClassifier::CircleClassifier(cv::Mat t_labeled_image)
	: m_labeled_image(t_labeled_image)
{}

CircleClassifier::~CircleClassifier()
{
}

void CircleClassifier::initContainers(Components& t_components)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		//std::cout << "i=" << i << " size=" << t_components.size() << std::endl;
		if (t_components.at(i).isContainer())
		{
			m_containers.push_back(t_components.at(i));
			std::cout << "new=" << t_components.at(i).getLabel() << std::endl;
		}
	}
	initChildren(t_components);
}

void CircleClassifier::initChildren(Components& t_components)
{
	for (int i = 0; i < t_components.size(); i++)
	{
		if (t_components.at(i).getContainer() != NULL)
		{
			//std::cout << "my_container=" << t_components.at(i).getContainer()->getLabel();
			for (int j = 0; j < m_containers.size(); j++)
			{
				//std::cout << "---container=" << m_containers.at(j).m_container->getLabel() << std::endl;
				if (m_containers.at(j).m_container->getLabel() == t_components.at(i).getContainer()->getLabel())
				{
					m_containers.at(j).addChild(t_components.at(i));
				}
			}
		}
	}
}

bool CircleClassifier::isCircle(Container t_container, std::vector<cv::Vec4i>& t_hierarchy)
{
	for (int i = 0; i < t_hierarchy.size(); i++)
	{
		if (t_hierarchy.at(i)[2] != -1)
		{
			return true;
		}
	}
	return false;
#if 0
	Component child = t_container.getChildren().at(0);
	int origin_x = child.getBoundingBox().x;
	int origin_y = child.getBoundingBox().y;
	int parent_label = t_container.m_container->getLabel();

	int i, j;
	i = j = origin_y;

	bool bounded_above = false;
	bool bounded_below = false;

	while (i < m_labeled_image.rows & !bounded_below)
	{
		if (parent_label == m_labeled_image.at<int>(i, origin_y))
		{
			bounded_below = true;
		}
		m_labeled_image.at<int>(i, origin_y) = 50;
		i++;
	}
	while (j > 0 & !bounded_above)
	{
		if (parent_label == m_labeled_image.at<int>(j, origin_y))
		{
			bounded_above = true;
		}
		m_labeled_image.at<int>(j, origin_y) = 50;
		j--;
	}
	i = j = 0;
	cv::Mat dst(m_labeled_image.size(), CV_8UC3);
	cv::Vec3b white = cv::Vec3b(255, 255, 255);
	cv::Vec3b color = cv::Vec3b(0, 0, 0);
	for (i; i < dst.rows; ++i)
	{
		for (j; j < dst.cols; ++j)
		{
			if (m_labeled_image.at<int>(i, j) == 50)
			{
				cv::Vec3b& pixel = dst.at<cv::Vec3b>(i, j);
				pixel = color;
			}
			else
			{
				cv::Vec3b& pixel = dst.at<cv::Vec3b>(i, j);
				pixel = white;
			}
		}
	}
	imwrite("./circle_test.jpg", dst);
	return bounded_above && bounded_below;
#endif
}

Containers CircleClassifier::getContainers()
{
	return m_containers;
}

Containers CircleClassifier::findCircles(ImageProcessor& t_image_processor, ComponentDetector& t_component_detector)
{
	Containers circles;
	for (int i = 0; i < m_containers.size(); i++)
	{
		std::vector<cv::Vec4i> hierarchy = t_image_processor.getHierarchy(m_containers.at(i), t_component_detector.m_labeled_image);
		//std::cout << "HIERARCHY AT " << i << std::endl;
		//for (int i = 0; i < hierarchy.size(); i++)
		//{
		//	std::cout << "[" << hierarchy.at(i)[0] << "," << hierarchy.at(i)[1] << "," << hierarchy.at(i)[2] << "," << hierarchy.at(i)[3] << "]\n";
		//}
		if (isCircle(m_containers.at(i), hierarchy))
		{
			m_containers.at(i).m_container->setClassified();
			for (int j = 0; j < m_containers.at(i).getChildren().size(); j++)
			{
				m_containers.at(i).getChildren().at(j).setClassified();
			}
			circles.push_back(m_containers.at(i));
		}
	}
	return circles;
}

void CircleClassifier::showCircles()
{
#if 0
	cv::Mat circles_image = m_labeled_image == findCircles().at(0).m_container->getLabel();
	for (int i = 1; i < findCircles().size(); i++)
	{
		//circles_image = circles_image | (circles_image == findCircles().at(i).m_container->getLabel());
	}
	cv::namedWindow("Circles", 1);
	cv::imshow("Circles", circles_image);
	cv::waitKey(0);
#endif
}

void CircleClassifier::displayContainerLabels()
{
	for (int i = 0; i < m_containers.size(); i++)
	{
		Component c = *m_containers.at(i).m_container;
		std::cout << c.getLabel() << std::endl;
	}
}
