#include <iostream>
#include <vector>

#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct coordinates {

    int x;
    int y;

};

int main(int argc, char** argv) {

    cv::Mat color_image;
    cv::Mat grey_image;
    cv::namedWindow("Video Player", cv::WINDOW_NORMAL);
    cv::VideoCapture cap(0);

    if (argc == 2 && std::string(argv[1]) == "-f") {

        std::cout << "set to fullscreen" << std::endl;
        cv::setWindowProperty("Video Player", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    }
    
    if (!cap.isOpened()) {

        std::cout << "No video stream detected." << std::endl;
        return -1;

    }

    while (true) {

        cap >> color_image;
	cv::cvtColor(color_image, grey_image, cv::COLOR_BGR2GRAY);

	if (grey_image.empty()) {

            break;

        }

        cv::CascadeClassifier faceCascade;
        faceCascade.load("resources/haarcascade_frontalface_default.xml");
        
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grey_image, faces, 1.1, 10);
        unsigned short int thickness = 2;
        
        for (int i = 0; i < faces.size(); ++i) {

            cv::rectangle(grey_image, faces[i].tl(), faces[i].br(), cv::Scalar(255, 255, 255), thickness, cv::LINE_8);

        }
        
        cv::imshow("Video Player", grey_image);
        char c = (char) cv::waitKey(25);
        if (c == 27) {

            break;

        }


    }
    return 0;

}
