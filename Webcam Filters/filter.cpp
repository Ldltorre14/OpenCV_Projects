#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>




void main() {
	//We read the image and declare Mat for every different function that we are going to use on the original image
	cv::Mat img = cv::imread("Resources/landscape.jpg");
	cv::Mat grayImg;
	cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
	cv::Mat smoothImg;
	cv::Mat cannyImg;
	cv::Mat laplaceImg;
	cv::Mat noiseImg;

	cv::GaussianBlur(img, smoothImg, cv::Size(5, 5), 1, 1);
	cv::Canny(img, cannyImg, 150, 300);
	cv::Laplacian(grayImg, laplaceImg, CV_8U);
	

	cv::imshow("Image", img);
	cv::imshow("Smooth", smoothImg);
	cv::imshow("Canny", cannyImg);
	cv::imshow("Laplace", laplaceImg);
	

	cv::waitKey(0);



}
