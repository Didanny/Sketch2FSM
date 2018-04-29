//#include "CircleDetector.h"
//#include "ImageProcessor.h"
//
//using namespace std;
//using namespace cv;
//#include "opencv2/core/core.hpp"
//
//#include "opencv2/highgui/highgui.hpp"
//
//#include <iostream>
//
//#include "opencv2\features2d.hpp"
//
///// Global Variables
//Mat img; Mat templ; Mat result;
//const char* image_window = "Source Image";
//const char* result_window = "Result window";
//
//int match_method;
//int max_Trackbar = 5;
//
///// Function Headers
//void MatchingMethod(int, void*);
//
//int main()
//{
//#pragma region "Circles"
//	// Setting image path, eventually will be user input
//	std::string image = "./../../test2.jpg";
//
//	// Initializing imageProcessor to work with the selected image
//	ImageProcessor imageProcessor(image);
//	cv::Mat src = imageProcessor.originalImage();
//
//	// Initializing circleDetector to work with the pre-processed image
//	CircleDetector circleDetector(imageProcessor.forCircleDetector());
//	Circles circlesTotal = circleDetector.detectAllCircles();
//
//	threshold(src, src, 165, 255, THRESH_BINARY);
//	//connectedComponents(src, src, 8, CV_32S);
//	//namedWindow("Connected Components", CV_WINDOW_AUTOSIZE);
//	//imshow("Connected Components", src);
//
//	//waitKey(0);
//#pragma endregion
//
//#pragma region "Template Matching Test"
//	img = src;
//	templ = imread("./templates/selfarrow3.jpg");
//
//	namedWindow(image_window, CV_WINDOW_AUTOSIZE);
//	namedWindow(result_window, CV_WINDOW_AUTOSIZE);
//
//	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	waitKey(0);
//#pragma endregion
//
//#pragma region "Draw Detected Circles"
//	//// Draw the circles detected
//	//for (size_t i = 0; i < circlesTotal.size(); i++)
//	//{
//	//	Point center(cvRound(circlesTotal[i][0]), cvRound(circlesTotal[i][1]));
//	//	int radius = cvRound(circlesTotal[i][2]);
//	//	// circle center
//	//	circle(src, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
//	//	// circle outline
//	//	circle(src, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
//	//}
//	//cout << "Num Circles: " << circlesTotal.size() << std::endl;
//	///// Show your results
//	//namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
//	//imshow("Hough Circle Transform Demo", src);
//
//	//waitKey(0);
//#pragma endregion
//	
//#pragma region "Contours"
//	//// Read image
//	//Mat im = imread("test.jpg", IMREAD_GRAYSCALE);
//
//	//// Set up the detector with default parameters.
//	//std::vector<KeyPoint> keypoints;
//	//SimpleBlobDetector detector = SimpleBlobDetector::create(im, keypoints);
//
//	//// Detect blobs.
//	//std::vector<KeyPoint> keypoints;
//	//detector.detect(im, keypoints);
//
//	//// Draw detected blobs as red circles.
//	//// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
//	//Mat im_with_keypoints;
//	//drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//
//	//// Show blobs
//	//imshow("keypoints", im_with_keypoints);
//	//waitKey(0);
//#pragma endregion
//
//	return 0;
//}
//
//void MatchingMethod(int, void*)
//{
//	/// Source image to display
//	Mat img_display;
//	img.copyTo(img_display);
//
//	/// Create the result matrix
//	int result_cols = img.cols - templ.cols + 1;
//	int result_rows = img.rows - templ.rows + 1;
//
//	result.create(result_rows, result_cols, CV_32FC1);
//
//	/// Do the Matching and Normalize
//	matchTemplate(img, templ, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/// Localizing the best match with minMaxLoc
//	double minVal; double maxVal; Point minLoc; Point maxLoc;
//	Point matchLoc;
//
//	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
//	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
//	{
//		matchLoc = minLoc;
//	}
//	else
//	{
//		matchLoc = maxLoc;
//	}
//
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	return;
//}

//#include <opencv2/core/utility.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
#include <iostream>
#include "ImageProcessor.h"
#include "CircleClassifier.h"
#include "Circle.h"
#include "ArrowClassifier.h"
#include "Arrow.h"
//#include <Windows.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stack>

//using namespace cv;
//using namespace std;

//Mat img;
//int threshval = 100;

//static void on_trackbar(int, void*)
//{
//	std::vector<Vec3b> colors(nLabels);
//	colors[0] = Vec3b(255, 255, 255);//background
//	for (int label = 1; label < nLabels; ++label) {
//		colors[label] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
//	}
//	Mat dst(img.size(), CV_8UC3);
//	for (int r = 0; r < dst.rows; ++r) {
//		for (int c = 0; c < dst.cols; ++c) {
//			int label = labelImage.at<int>(r, c);
//			Vec3b &pixel = dst.at<Vec3b>(r, c);
//			pixel = colors[label];
//		}
//	}
//
//	imshow("Connected Components", dst);
//}

//static void help()
//{
//	std::cout << "\n This program demonstrates connected components and use of the trackbar\n"
//		"Usage: \n"
//		"  ./connected_components <image(../data/stuff.jpg as default)>\n"
//		"The image is converted to grayscale and displayed, another image has a trackbar\n"
//		"that controls thresholding and thereby the extracted contours which are drawn in color\n";
//}

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

	Containers containers;
	component_detector.findContainers();
	Components components = component_detector.getComponents();

	CircleClassifier circle_classifier(component_detector.getLabeledImage());
	circle_classifier.initContainers(components);
	//circle_classifier.initChildren(components);
	containers = circle_classifier.getContainers();
	circle_classifier.displayContainerLabels();
	//circle_classifier.showCircles();


#if 0

	cv::Mat dst = cv::Mat(img.size(), CV_8UC3);
	cv::Vec3b colors[2] = { cv::Vec3b(255, 255, 255), cv::Vec3b(0, 255, 0) };

	for (int r = 0; r < dst.rows; ++r) {
		for (int c = 0; c < dst.cols; ++c) {
			int label = z.at<int>(r, c);
			cv::Vec3b &pixel = dst.at<cv::Vec3b>(r, c);
			pixel = colors[std::min(label, 1)];
		}
	}

	cv::imshow("Labels", dst);

#endif
	//cv::imshow("Container", image_processor.containerImage(containers.at(3), component_detector.m_labeled_image));

#if 0
	cv::Mat src, src_gray, canny_output;
	src = image_processor.containerImage(containers.at(3), component_detector.m_labeled_image);
	cv::cvtColor(src, src_gray, CV_BGR2GRAY);
	cv::blur(src_gray, src_gray, cv::Size(3, 3));

	cv::Canny(src_gray, canny_output, 100, 200, 3);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (int i = 0; i < hierarchy.size(); i++)
	{
		std::cout << "[" << hierarchy.at(i)[0] << "," << hierarchy.at(i)[1] << "," << hierarchy.at(i)[2] << "," << hierarchy.at(i)[3] << "]\n";
	}
#endif

	std::vector<cv::Vec4i> hierarchy = image_processor.getHierarchy(containers.at(1), component_detector.m_labeled_image);

	Containers circles_t = circle_classifier.findCircles(image_processor, component_detector);
	for (int i = 0; i < circles_t.size(); i++)
	{
		std::cout << circles_t.at(i).m_container->getLabel() << "\n";
	}

	Circles circles(circle_classifier.findCircles(image_processor, component_detector));

	ComponentsWithStats chars = circles.getChars();
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

	cv::Mat x = z != 0;
	for (int i = 0; i < labels.size(); i++)
	{
		x = x & (z != labels.at(i));
	}
	cv::imshow("X", x);


	cv::imshow("Arrow0", image_processor.componentImage(arrow_classifier.m_arrows.at(0), component_detector.getLabeledImage()));
	cv::Mat arrow_0 = image_processor.componentImage(arrow_classifier.m_arrows.at(2), component_detector.getLabeledImage());

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

#if 1
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
	Arrow arrow0(corners);
	arrow0.initArrow();

#if 1
	cv::circle(arrow_0copy, arrow0.m_start, r, cv::Scalar(0, 255, 0), -1, 8, 0);
	cv::circle(arrow_0copy, arrow0.m_end, r, cv::Scalar(0, 0, 255), -1, 8, 0);
	cv::circle(arrow_0copy, arrow0.start2, r, cv::Scalar(255, 0, 0), -1, 8, 0);
#endif
	int index;
	//arrow0.getNearestPoint(corners[0], index);


#if 0
	cv::Point2f current_point = corners[0];
	cv::Point2f nearest_point;
	float min_distance = 99999999;
	for (int i = 0; i < corners.size(); i++)
	{
		if (visited.at(i) || current_point == corners.at(i)) continue;

		cv::Point2f next_point = corners.at(i);
		visited.at(i) = true;
		float current_distance = sqrt(pow((current_point.x - next_point.x), 2) + pow((current_point.y - next_point.y), 2));

		if (current_distance < min_distance)
		{
			min_distance = current_distance;
			nearest_point = next_point;
		}
	}
#endif

#if 0
	//cv::approxPolyDP(corners, arrow_0copy, 10, true);


	//cv::line(arrow_0copy, corners[0], corners[index], cv::Scalar(0, 255, 0));
	cv::Point2f current_point = arrow0.m_corners.at(0);
	cv::Point2f next_point;
	int next_index = arrow0.getNearestPoint(current_point);
	double previous_slope;
	double current_slope;
	previous_slope = 0;
	bool first = true;
	std::vector<cv::Point2f> ends;
	std::cout << "RATIOS:\n";
	double max_angle = 0;
	std::stack<cv::Point2f> end_stack;
	int end_index = 0;
	while (next_index < arrow0.m_corners.size() && next_index > -1)
	{
		//if (arrow0.m_visited.at(i)) continue;
		next_point = arrow0.m_corners.at(next_index);
		arrow0.m_visited.at(next_index) = true;

		current_slope = (next_point.y - current_point.y) / (next_point.x - current_point.x);
		std::cout << "slope=" << current_slope << "\n";
		cv::line(arrow_0copy, current_point, next_point, cv::Scalar(0, 255, 0));
		current_point = next_point;
		next_index = arrow0.getNearestPoint(current_point);

		double angle;
		if (!first) 
		{
			angle = abs(atan((current_slope - previous_slope) / (1 + (current_slope * previous_slope))));
			std::cout << angle << "\n";
			if (angle > max_angle)
			{
				end_stack.push(current_point);
			}
			//if (angle > 1.39 && angle < 1.75)
			//{
			//	ends.push_back(current_point);
			//	circle(arrow_0copy, current_point, r, cv::Scalar(255, 0, 0), -1, 8, 0);
			//}
		}
		first = false;
		previous_slope = current_slope;
		end_index++;
	}
	float sum_x = 0;
	float sum_y = 0;
	for (int i = 0; i < 3; i++)
	{
		circle(arrow_0copy, end_stack.top(), r, cv::Scalar(255, 0, 0), -1, 8, 0);
		sum_x += end_stack.top().x;
		sum_y += end_stack.top().y;
		end_stack.pop();
	}
	cv::Point2f end(sum_x / 3, sum_y / 3);
	cv::Point2f s1 = arrow0.m_corners.at(0);
	cv::Point2f s2 = arrow0.m_corners.at(end_index - 1);
	float d1 = sqrt(pow((s1.x - end.x), 2) + pow((s1.y - end.y), 2));
	float d2 = sqrt(pow((s2.x - end.x), 2) + pow((s2.y - end.y), 2));
	if (d1 > d2)
	{
		// start is s2
	}
	else
	{
		// start is s1
	}
#endif





#if 0
	current_point = corners[1];
	for (int i = 1; i < corners.size(); i++)
	{
		cv::Point2f nearest_point;
		float min_distance = 99999999;
		for (int i = 0; i < corners.size(); i++)
		{
			if (visited.at(i) || current_point == corners.at(i)) continue;

			cv::Point2f next_point = corners.at(i);
			visited.at(i) = true;
			float current_distance = sqrt(pow((current_point.x - next_point.x), 2) + pow((current_point.y - next_point.y), 2));

			if (current_distance < min_distance)
			{
				min_distance = current_distance;
				nearest_point = next_point;
			}
		}
		cv::line(arrow_0copy, current_point, nearest_point, cv::Scalar(0, 255, 0));
		current_point = nearest_point;
	}
#endif



	// Edge detection
	cv::Mat dst;
	//cv::Canny(arrow_0, dst, 50, 200, 3);
	// Copy edges to the images that will display the results in BGR
	cv::Mat cdst;
	cvtColor(dst, cdst, CV_GRAY2BGR);

#if 0
	std::vector<cv::Vec2f> lines; // will hold the results of the detection
	cv::HoughLines(dst, lines, 1, CV_PI / 180, 50, 0, 0); // runs the actual detection

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(cdst, pt1, pt2, cv::Scalar(0, 255, 0), 3, CV_AA);
	}


	std::vector<cv::Vec4i> linesP; // will hold the results of the detection
	cv::HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 10, 10); // runs the actual detection
														  // Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		cv::Vec4i l = linesP[i];
		cv::line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, CV_AA);
	}

	std::cout << "LINES DETECTED: " << linesP.size() << std::endl;
#endif



	cv::imshow("Arrow Features", arrow_0copy);
	//cv::imshow("Arrow Features2", cdst);
	cv::waitKey(0);

#if 0
	std::vector<int> labels;
	for (int i = 0; i < components.size(); i++)
	{
		//std::cout << components.at(i).isContainer() << std::endl;
	}
	for (int i = 0; i < components.size(); i++)
	{
		//if (components.at(i).isContainer()) labels.push_back(components.at(i).m_label);
	}

	for (int i = 0; i < components.size(); i++)
	{
		for (int j = 0; j < containers.size(); j++)
		{
			if (components.at(i).getContainer() != NULL && components.at(i).getContainer()->m_label == containers.at(j).m_container->m_label)
			{
				containers.at(j).addChild(components.at(i));
			}
		}
	}

	for (int i = 0; i < components.size(); i++)
	{
		std::cout << "component " << i << std::endl;
		if (components.at(i).getContainer() == NULL)
		{
			std::cout << "--NULL" << std::endl;
		}
		else 
		{
			std::cout << "--YES--" << components.at(i).getContainer()->getLabel() << std::endl;
		}
	}
	std::cout << "\n\n\n";

	for (int i = 0; i < components.size(); i++)
	{
		if (components.at(i).getContainer() != NULL)
		{
			std::cout << "my_container=" << components.at(i).getContainer()->getLabel();
			for (int j = 0; j < containers.size(); j++)
			{
				std::cout << "---container=" << containers.at(j).m_container->getLabel() << std::endl;
				if (containers.at(j).m_container->getLabel() == components.at(i).getContainer()->getLabel())
				{
					containers.at(j).addChild(components.at(i));
				}
			}
		}
	}
#endif

	//int l = 0;
	//for (int i = 0; i < containers.at(i).getChildren().size(); i++)
	//{
	//	labels.push_back(containers.at(i).getChildren().at(i).m_label);
	//}


#pragma region Circle Detector (BROKEN)
#if 0

	std::cout << "Circles" << std::endl;
	Containers circles = circle_classifier.findCircles();
	std::vector<int> labels;
	for (int i = 0; i < circles.size(); i++)
	{
		std::cout << circles.at(i).m_container->getLabel() << std::endl;
	}

#endif
#pragma endregion


	// The 1 in "State 1"
	cv::rectangle(img, components.at(12).getBoundingBox(), cv::Scalar(200, 0, 0), 3);
	// Should be the inner circle of State 1
	//cv::rectangle(img, components.at(14).getContainer()->getBoundingBox(), cv::Scalar(200, 0, 0), 3);

#pragma endregion

#pragma region Testing Component::contains()
	//// Drawing the contained components
	//for (int i = 0; i < components.size(); i++)
	//{
	//	for (int j = 0; j < components.size(); j++)
	//	{
	//		if (components.at(j).contains(components.at(i)))
	//		{
	//			std::cout << "contains: " << i << std::endl;
	//			cv::rectangle(img, components.at(i).getBoundingBox(), cv::Scalar(200, 0, 0), 3);
	//		}
	//	}
	//}
#pragma endregion

#pragma region Debugging .contains()
	//// t in "State 2"
	//cv::rectangle(img, components.at(10).getBoundingBox(), cv::Scalar(200, 0, 0), 3);

	//// Circle around "State 2"
	//cv::rectangle(img, components.at(4).getBoundingBox(), cv::Scalar(200, 0, 0), 3);

	//// Should print 1
	//std::cout << components.at(4).contains(components.at(10)) << std::endl;
	//// SHould print 0
	//std::cout << components.at(10).contains(components.at(4)) << std::endl;
#pragma endregion

#pragma region Debugging CircleClassifier

#pragma endregion

#if 0
	cv::Mat y = image_processor.forComponentDetector();

	cv::namedWindow("Image3", 1);
	cv::imshow("Image3", img);

	cv::Mat z = component_detector.getLabeledImage();

	//cv::namedWindow("Labels", 1);
	//cv::imshow("Labels", (z == (7) | z == (8) | z == (10) | z == (26)));

	//Container big_circle = containers.at(0);
	//Container other_circle = containers.at(1);
	//Container small_circle = containers.at(2);
	//Container arrow = containers.at(3);



	//std::cout << big_circle.getChildren().size() << std::endl;
	//std::cout << other_circle.getChildren().size() << std::endl;
	//std::cout << small_circle.getChildren().size() << std::endl;
	//std::cout << arrow.getChildren().size() << std::endl;

	cv::Mat x = z == labels.at(0);
	for (int i = 0; i < labels.size(); i++)
	{
		x = x | (z == labels.at(i));
	}
	cv::imshow("Labels", x);
	x = x | (z == containers.at(l).m_container->m_label);

	//std::cout << (z == 1) << std::endl;
#endif
	cv::waitKey(0);

	system("pause");

#if 0
	//if (img.empty())
	//{
	//	cout << "Could not read input image file: " << inputImage << endl;
	//	return -1;
	//}
	
	//GaussianBlur(img, img, cv::Size(9, 9), 1, 1);

	//namedWindow("Image", 1);
	//imshow("Image", img);

	//threshold(img, img, 170, 255, THRESH_BINARY);

	//namedWindow("Image2", 1);
	//imshow("Image2", img);

	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);
	Mat labelImage(img.size(), CV_32S);
	Mat stats;
	Mat centroids;
	//cout << "bw= " << bw << endl;
	int nLabels = connectedComponentsWithStats(bw, labelImage, stats, centroids, 8);
	cout << "nLabels= " << nLabels << endl;
	Mat image;
	img.copyTo(image);
	//threshold(image, image, 0, 255, THRESH_BINARY);

	int num = 0;
	for (int i = 0; i<stats.rows; i++)
	{
		int x = stats.at<int>(Point(0, i));
		int y = stats.at<int>(Point(1, i));
		int w = stats.at<int>(Point(2, i));
		int h = stats.at<int>(Point(3, i));
		int lol = stats.at<int>(Point(4, i));
		//int lol3 = stats.at<int>(Point(6, i));
		double cx = 0;
		double cy = 0;

		if (lol < 10) num--;

		cx = centroids.at<double>(i, 0);
		cy = centroids.at<double>(i, 1);

		if (lol >= 10) std::cout << "x=" << x << " y=" << y << " w=" << w << " h=" << h << " area=" << lol << " cx=" << cx << " cy=" << cy << std::endl;

		Scalar color(200, 0, 0);
		Rect rect(x, y, w, h);
		if (lol >= 10) cv::rectangle(image, rect, color, 3);
		num++;
	}
	std::cout << "stats.rows= " << stats.rows << endl;
	std::cout << "There are: " << num << endl;

	namedWindow("Image3", 1);
	imshow("Image3", image);

	//createTrackbar("Threshold", "Connected Components", &threshval, 255, on_trackbar);
	//on_trackbar(threshval, 0);

	waitKey(0);
	return 0;
#endif
}