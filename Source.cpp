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

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
int threshval = 100;

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

static void help()
{
	cout << "\n This program demonstrates connected components and use of the trackbar\n"
		"Usage: \n"
		"  ./connected_components <image(../data/stuff.jpg as default)>\n"
		"The image is converted to grayscale and displayed, another image has a trackbar\n"
		"that controls thresholding and thereby the extracted contours which are drawn in color\n";
}

const char* keys =
{
	"{help h||}{@image|../data/stuff.jpg|image for converting to a grayscale}"
};

int main(int argc, const char** argv)
{
	//CommandLineParser parser(argc, argv, keys);
	//if (parser.has("help"))
	//{
	//	help();
	//	return 0;
	//}
	//string inputImage = parser.get<string>(0);
	img = imread("./../../test2.jpg", 0);

	//if (img.empty())
	//{
	//	cout << "Could not read input image file: " << inputImage << endl;
	//	return -1;
	//}
	GaussianBlur(img, img, cv::Size(9, 9), 1, 1);

	namedWindow("Image", 1);
	imshow("Image", img);

	threshold(img, img, 170, 255, THRESH_BINARY);

	namedWindow("Image2", 1);
	imshow("Image2", img);

	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);
	Mat labelImage(img.size(), CV_32S);
	Mat stats;
	Mat centroids;
	int nLabels = connectedComponentsWithStats(bw, labelImage, stats, centroids, 8);
	Mat image;
	img.copyTo(image);
	//threshold(image, image, 0, 255, THRESH_BINARY);

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

		cx = centroids.at<double>(i, 0);
		cy = centroids.at<double>(i, 1);

		std::cout << "x=" << x << " y=" << y << " w=" << w << " h=" << h << " area=" << lol << " cx=" << cx << " cy=" << cy << std::endl;

		Scalar color(200, 0, 0);
		Rect rect(x, y, w, h);
		cv::rectangle(image, rect, color, 3);
	}
	std::cout << "There are: " << stats.rows << endl;

	namedWindow("Image3", 1);
	imshow("Image3", image);

	//createTrackbar("Threshold", "Connected Components", &threshval, 255, on_trackbar);
	//on_trackbar(threshval, 0);

	waitKey(0);
	return 0;
}