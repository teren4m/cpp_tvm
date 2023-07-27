#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <receipt_nn.h>

using namespace cv;
using namespace std::chrono;

bool IsReceipt(Mat frame);

void DrawCircle(Mat img, Point center);

milliseconds GetTime();

int main(int argc, char **argv)
{

    VideoCapture camera(0);

    // array to hold image
    Mat frame;
    Point circle_point(30, 30);

    // display the frame until you press a keygit adds
    while (1)
    {
        milliseconds ms_prev = GetTime();
        // capture the next frame from the webcam
        camera >> frame;
        // show the image on the window
        if (IsReceipt(frame))
        {
            DrawCircle(frame, circle_point);
        }
        milliseconds ms_curr = GetTime();
        int diff = (ms_curr - ms_prev).count();
        int fps = 1000 / diff;
        std::cout << "Fps: " << std::to_string(fps) << std::endl;
        imshow("some", frame);
        // wait (10ms) for esc key to be pressed to stop
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}

void DrawCircle(Mat img, Point center)
{
    circle(img,
           center,
           center.x,
           Scalar(0, 0, 255),
           FILLED,
           LINE_8);
}

bool IsReceipt(Mat frame)
{
    return detect_receipt();
}

milliseconds GetTime()
{
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());
}