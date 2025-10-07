#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

struct coordinates {

    int x;
    int y;

};

int main(int argc, char** argv) {

    cv::Mat image;
    cv::namedWindow("Video Player", cv::WINDOW_NORMAL);
    cv::VideoCapture cap(0);

    if (argc == 2 && std::string(argv[1]) == "-f") {

        std::cout << "set to fullscreen" << std::endl;
        cv::setWindowProperty("Video Player", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    }
    
    assert(cap.isOpened() && "No video stream detected!");
    while (true) {

        cap >> image;
        if (image.empty()) {

            break;

        }

        cv::CascadeClassifier faceCascade;
        faceCascade.load("resources/haarcascade_frontalface_default.xml");
        
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(image, faces, 1.1, 10);
        unsigned short int thickness = 2;
        
        for (int i = 0; i < faces.size(); ++i) {

            cv::rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(255, 255, 255), thickness, cv::LINE_8);

        }
        
        cv::imshow("Video Player", image);
        char c = (char) cv::waitKey(25);
        if (c == 27) {

            break;

        }


    }
    return 0;

}