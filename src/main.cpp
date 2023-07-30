#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <receipt_nn.hpp>

using namespace cv;
using namespace std::chrono;

bool IsReceipt(Mat frame);

void DrawCircle(Mat img, Point center);

milliseconds GetTime();

ReceiptDetect receiptDetect;

int main(int argc, char **argv)
{

    VideoCapture camera(0);

    // array to hold image
    Mat frame;
    Point circle_point(30, 30);
    milliseconds ms_prev_curr = GetTime();

    // display the frame until you press a keygit adds
    while (1)
    {
        milliseconds ms_prev = GetTime();
        // capture the next frame from the webcam
        camera >> frame;
        // show the image on the window
        cv::Mat img_dst;
        cv::resize(frame, img_dst, cv::Size(200, 200), 0, 0, cv::INTER_AREA);
        if (IsReceipt(img_dst))
        {
            DrawCircle(frame, circle_point);
        }
        milliseconds ms_curr = GetTime();
        int diff = (ms_curr - ms_prev).count();
        int fps = 1000 / diff;
        if ((ms_curr.count() - ms_prev_curr.count()) > 2000)
        {
            std::cout << "Fps: " << std::to_string(fps) << std::endl;
            ms_prev_curr = ms_curr;
        }
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
    unsigned char *dataMat = frame.data;
    return receiptDetect.detect_receipt((char *)dataMat);
}

milliseconds GetTime()
{
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());
}