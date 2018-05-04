#include <iostream>
#include "ImageProcessor.h"
#include "CircleClassifier.h"
#include "Circle.h"
#include "ArrowClassifier.h"
#include "Arrow.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stack>
#include <iostream>
#include <string>
#include <thread>
#include "SketchAnalyzer.h"

const char* keys =
{
	"{help h||}{@image|../data/stuff.jpg|image for converting to a grayscale}"
};

std::vector<int> vect;
std::vector<int>& Vect()
{
	return vect;
}

int main(int argc, const char** argv)
{

#pragma region SketchAnalyzer

	SketchAnalyzer sa;
	sa.loadImage("./../../test2.jpg", 17);
	cv::imshow("SA IMG", sa.m_image_processor->originalImage());
	sa.findConnectedComponents();
	//cv::imshow("SA Labels", sa.m_component_detector->getLabeledImage());
	sa.findContainers();
	sa.findCircles();
	sa.findCharacters();
	sa.findArrows();
	sa.parseLabels();
	sa.createStates();
	sa.createTransitions();
	sa.outputFile();

	std::cout << "CONTAINERS\n";
	for (int i = 0; i < sa.m_circle_classifier->getContainers().size(); i++)
	{
		std::cout << sa.m_circle_classifier->getContainers().at(i).m_container->getLabel() << std::endl;
	}
	std::cout << "CIRCLES\n";
	for (int i = 0; i < sa.m_circles->getLabels().size(); i++)
	{
		std::cout << sa.m_circles->getLabels().at(i) << std::endl;
	}
	std::cout << "CHARS\n";
	for (int i = 0; i < sa.m_chars.getLabels().size(); i++)
	{
		std::cout << sa.m_chars.getLabels().at(i) << std::endl;
	}
	std::cout << "ARROWS\n";
	std::cout << "This many arrows " << sa.m_arrow_classifier->m_arrows_i.size()
	<< sa.m_arrow_classifier->m_arrows.size() << "\n";
	for (int i = 0; i < sa.m_circles->getLabels().size(); i++)
	{
		std::cout << sa.m_circles->getLabels().at(i) << std::endl;
	}
	std::cout << "ARROW CHARS\n";
	for (int i = 0; i < sa.m_arrow_classifier->getLabelLabels().size(); i++)
	{
		std::cout << "Arrow " << i << std::endl;
	}
	std::cout << "STATES\n";
	for (int i = 0; i < sa.m_states.size(); i++)
	{
		std::cout << sa.m_states.at(i).m_name << " " << sa.m_states.at(i).m_circle.getLabel() << " " << sa.m_states.at(i).m_circle.getCentroid().y << "," << sa.m_states.at(i).m_circle.getCentroid().x << std::endl;
	}
	std::cout << "TRANSITIONS\n";
	for (int i = 0; i < sa.m_transitions.size(); i++)
	{
		std::cout << sa.m_transitions.at(i).m_label << std::endl;
	}
	cv::imshow("Arrows", sa.m_image_processor->labelIMage(sa.m_arrow_classifier->getLabels(), sa.m_component_detector->getLabeledImage()));

#pragma endregion

#pragma region Setup Detector
	//CommandLineParser parser(argc, argv, keys);
	//if (parser.has("help"))
	//{
	//	help();
	//	return 0;
	//}
	//string inputImage = parser.get<string>(0);
	cv::Mat img = cv::imread("./../../test2.jpg", 0);
	cv::threshold(img, img, 170, 255, cv::THRESH_BINARY);

	ImageProcessor image_processor("./../../test2.jpg");
	cv::imshow("ImgProcessor", image_processor.forComponentDetector());
	ComponentDetector component_detector(image_processor.forComponentDetector());
	component_detector.detectComponents();

	//Components components = component_detector.getComponents();

	//for (int i = 0; i < components.size(); i++)
	//{
	//	cv::rectangle(img, components.at(i).getBoundingBox(), cv::Scalar(200,0,0), 3);
	//	std::cout << i << std::endl;
	//}
#pragma endregion

#pragma region Finding Containers

	//Containers containers;
	component_detector.findContainers();
	Components components = component_detector.getComponents();

	CircleClassifier circle_classifier(component_detector.getLabeledImage());
	circle_classifier.initContainers(components);
	//circle_classifier.initChildren(components);
	//containers = circle_classifier.getContainers();
	circle_classifier.displayContainerLabels();
	//circle_classifier.showCircles();

	//std::vector<cv::Vec4i> hierarchy = image_processor.getHierarchy(containers.at(1), component_detector.m_labeled_image);

	Containers circles_t = circle_classifier.findCircles(image_processor, component_detector);
	for (int i = 0; i < circles_t.size(); i++)
	{
		std::cout << circles_t.at(i).m_container->getLabel() << "\n";
	}

	Circles circles(circle_classifier.findCircles(image_processor, component_detector));

	CharacterClassifier chars = circles.getChars();
	chars.findChars(components);

	std::vector<int> labels_all = circles.getLabels();
	std::vector<int> labels2 = chars.getLabels();

	labels_all.insert(labels_all.end(), labels2.begin(), labels2.end());

	ArrowClassifier arrow_classifier(components, labels_all);

	std::vector<int> labels = arrow_classifier.getLabels();
	std::cout << "ARROW LABELS:" << "\n";
	for (int i = 0; i < labels.size(); i++)
	{
		std::cout << labels.at(i) << "\n";
	}

	//for (int i = 0; i < components.size(); i++)
	//{
	//	if (!components.at(i).isClassified()) labels.push_back(components.at(i).getLabel());
	//}

	std::cout << chars.getMeanHeight() << " stdev: " << chars.getStdevHeight() << std::endl;
	std::cout << chars.getMeanWidth() << " stdev: " << chars.getStdevWidth() << std::endl;

	cv::Mat z = component_detector.getLabeledImage();

	cv::Mat x = z != 1 & z != 4 & z != 31;
	//for (int i = 0; i < labels.size(); i++)
	//{
	//	x = x & (z != labels.at(i));
	//}
	cv::imshow("X", x);


	cv::imshow("Arrow0", image_processor.componentImage(arrow_classifier.m_arrows.at(0), component_detector.getLabeledImage()));
	cv::Mat arrow_0 = image_processor.componentImage(arrow_classifier.m_arrows.at(0), component_detector.getLabeledImage());

#pragma region Corners
	std::vector<cv::Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	cv::Mat arrow_grey;
	cv::cvtColor(arrow_0, arrow_grey, CV_BGR2GRAY);

	goodFeaturesToTrack(arrow_grey,
		corners,
		100,
		qualityLevel,
		minDistance,
		cv::Mat(),
		blockSize,
		useHarrisDetector,
		k);

	cv::RNG rng(12345);
	cv::Mat arrow_0copy;
	arrow_0.copyTo(arrow_0copy);
	std::cout << "** Number of corners detected: " << corners.size() << std::endl;
	int r = 4;

#if 0
	// Drawing the corners
	for (int i = 0; i < corners.size(); i++)
	{
		circle(arrow_0copy, corners[i], r, cv::Scalar(0,0,255), -1, 8, 0);
		if (i == 0) circle(arrow_0copy, corners[i], r, cv::Scalar(0, 255, 0), -1, 8, 0);
		std::cout << corners[i].x << ":" << corners[i].y << "\n";
	}
#endif
#pragma endregion


	std::vector<bool> visited;
	
	// Initializing visited
	for (int i = 0; i < corners.size(); i++)
	{
		visited.push_back(false);
	}

	// Finding the nearest point
	/*Arrow arrow0(corners);
	arrow0.initArrow();*/

	int index;
	//arrow0.getNearestPoint(corners[0], index);

	// Edge detection
	cv::Mat dst;
	//cv::Canny(arrow_0, dst, 50, 200, 3);
	// Copy edges to the images that will display the results in BGR
	cv::Mat cdst;
	cvtColor(dst, cdst, CV_GRAY2BGR);

	cv::imshow("Arrow Features", arrow_0copy);
	//cv::imshow("Arrow Features2", cdst);
	cv::waitKey(0);

	cv::waitKey(0);

	system("pause");
}