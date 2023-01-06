#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>


//////////////
//////PROJECT 3 - LICENSE PLATE DETECTOR
//////////////






void main() {

	cv::VideoCapture cap(0);
	cv::Mat img;

	cv::CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_frontalface_default.xml");

	std::vector<cv::Rect> plates;

	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++) {
			cv::Mat imgCrop = img(plates[i]);
			//cv::imshow(std::to_string(i), cropImage);
			cv::imwrite("Resources/Plates/" + std::to_string(i) + ".png",imgCrop);
			cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(255, 0, 255), 3);
		}

		cv::imshow("image", img);
		cv::waitKey(1);
	}
	

}
