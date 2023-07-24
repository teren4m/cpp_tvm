#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std::chrono;

int main(int argc, char **argv)
{
    VideoCapture camera(0);
    if (!camera.isOpened())
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    // cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

    // // array to hold image
    // cv::Mat frame;

    // // display the frame until you press a keygit adds   
    // while (1)
    // {
    //     milliseconds ms = duration_cast<milliseconds>(
    //     system_clock::now().time_since_epoch());
    //     // capture the next frame from the webcam
    //     camera >> frame;
    //     // show the image on the window
    //     cv::imshow(std::to_string(ms.count()), frame);
    //     // wait (10ms) for esc key to be pressed to stop
    //     if (cv::waitKey(10) == 27)
    //         break;
    // }
    return 0;
}