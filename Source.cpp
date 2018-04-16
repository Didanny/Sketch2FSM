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
	ComponentDetector component_detector(img /*image_processor.forComponentDetector()*/);
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

	std::vector<int> labels;
	int l = 0;
	for (int i = 0; i < containers.at(l).getChildren().size(); i++)
	{
		labels.push_back(containers.at(l).getChildren().at(i).m_label);
	}

	cv::Mat z = component_detector.getLabeledImage();

	cv::Mat x = z == containers.at(l).m_container->m_label;
	for (int i = 0; i < labels.size(); i++)
	{
		x = x | (z == labels.at(i));
	}


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