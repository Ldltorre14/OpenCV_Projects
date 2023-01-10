#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

std::vector<cv::Rect> plates;


int main() {
	cv::Mat img = cv::imread("Resources/me.jpg");
	cv::Mat crop;
	cv::VideoCapture cap(0);
	cv::CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_frontalface_default.xml");

	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 3);

		for (int i = 0; i < plates.size(); i++) {
			crop = img(plates[i]);
			cv::line(img, plates[i].tl(), plates[i].br(), cv::Scalar(0, 255, 255), 2);
			cv::line(img, cv::Point(plates[i].x,plates[i].y + plates[i].height), cv::Point(plates[i].x + plates[i].width,plates[i].y), cv::Scalar(0, 255, 255), 2);
			cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(0, 255, 255), 3);
			cv::putText(img, "Leonardo", { plates[i].x, plates[i].y + plates[i].height + 20 }, cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 255), 1);
		}

		cv::imshow("Image", img);
		//cv::imshow("Crop", crop);
		cv::waitKey(1);
	}
	

}
