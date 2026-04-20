#include <iostream>
#include <vector>

#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

const char* WINDOW_NAME = "Video Player";
const char* CASCADE_FILE_PATH = "resources/haarcascade_frontalface_default.xml";
const unsigned short int RECT_BORDER_THICKNESS = 2;
bool USE_GREYSCALE_IMAGE = true;

struct coordinates {
    int x;
    int y;
};

void VideoCapture_CheckForFailure(const cv::VideoCapture& cap) {
    if (!cap.isOpened()) {
        throw std::runtime_error("No video stream detected.");
    }
}

void ImageCapture_CheckForFailure(const cv::Mat& image) {
    if (image.empty()) {
        throw std::runtime_error("Image empty. Exiting...");
    }
}

void LoadCascade(cv::CascadeClassifier& faceCascade, const char* FilePath) {
    if (!faceCascade.load(FilePath)) {
        throw std::runtime_error("Failed to load cascade file. Exiting...");
    }
}

void SetFullscreen(const char* Window_Name) {
    std::cout << "set to fullscreen" << std::endl;
    cv::setWindowProperty(Window_Name, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
}

void SetColor() {
    USE_GREYSCALE_IMAGE = false;
}

void ArgumentCheck(int argc, char** argv, const char* Window_Name) {

    for (int i = 1; i < argc; ++i) {

        if (argv[i] == "-f" || argv[i] == "-fullscreen") {
            SetFullscreen(Window_Name);
        }

        if (argv[i] == "-c" || argv[i] == "-color") {
            SetColor();
        }

    }

};



int main(int argc, char** argv) {

    cv::namedWindow(Window_Name, cv::WINDOW_NORMAL);
    cv::Mat image;
    std::vector<cv::Rect> faces;
    char KeyPressed;

    cv::VideoCapture cap(0);
    VideoCapture_CheckForFailure(cap);
    
    cv::CascadeClassifier faceCascade;
    LoadCascadeFromFile(faceCascade, CASCADE_FILE_PATH);
    
    ArgumentCheck(argc, argv, Window_Name);
    
    while (true) {

        faces.clear();

        cap >> image;
        ImageCapture_CheckForFailure(image);

        if (USE_GREYSCALE_IMAGE == true) {
            cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
        }

        faceCascade.detectMultiScale(image, faces, 1.1, 10);
        
        for (int i = 0; i < faces.size(); ++i) {
            cv::rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(255, 255, 255), RECT_BORDER_THICKNESS, cv::LINE_8);
        }
        
        cv::imshow(WINDOW_NAME, image);

        KeyPressed = (char)cv::waitKey(25);
        if (KeyPressed == 27) {
            break;
        }

    }

    return 0;

}
