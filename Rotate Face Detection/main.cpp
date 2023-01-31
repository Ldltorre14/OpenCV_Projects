#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

std::vector<cv::Rect> plates;


int main() {
	cv::Mat img,rotate90,rotate180,rotate270;
	cv::VideoCapture cap(0, cv::CAP_DSHOW);
	cv::CascadeClassifier cascade;
	cascade.load("Resources/haarcascade_frontalface_default.xml");

	while (true) {
		cap.read(img);
		cv::rotate(img, rotate90, cv::ROTATE_90_CLOCKWISE);
		cv::rotate(img, rotate180, cv::ROTATE_180);
		cv::rotate(img, rotate270, cv::ROTATE_90_COUNTERCLOCKWISE);

		/*cascade.detectMultiScale(img, plates);
		
		cv::rotate(img, rotate90, cv::ROTATE_90_CLOCKWISE);
		cv::rotate(img, rotate180, cv::ROTATE_180);
		cv::rotate(img, rotate270, cv::ROTATE_90_COUNTERCLOCKWISE);
		
		for (int i = 0; i < plates.size(); i++) {
			cv::rectangle(img, plates[i].tl(),plates[i].br(), cv::Scalar(255, 255, 255),3);
			cv::rectangle(rotate90, plates[i].tl(), plates[i].br(), cv::Scalar(255, 255, 255), 3);
			cv::rectangle(rotate180, plates[i].tl(), plates[i].br(), cv::Scalar(255, 255, 255), 3);
			cv::rectangle(rotate270, plates[i].tl(), plates[i].br(), cv::Scalar(255, 255, 255), 3);
		}*/

		cv::imshow("IMG", img);
		cv::imshow("ROTATE 90°", rotate90);
		cv::imshow("ROTATE 180°", rotate180);
		cv::imshow("ROTATE 270°", rotate270);
		cv::waitKey(1);
	}
}
